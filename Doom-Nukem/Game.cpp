#include "Game.h"
#include "RaycastingEngine.h"
#include <windows.h>

#include "GeneratedTextureGenerator.h"

namespace junk
{
std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

}


namespace doom_nukem {


Game::Game() {

}

Game::~Game()
{
    clean();
}

void Game::init(const char *title, int xPos, int yPos, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::exception("Failed to init SDL");
    }
    _window = SDL_CreateWindow(
        title,
        xPos, yPos,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if (_window == nullptr) {
        throw std::exception("Could not create window");
    }

	_screenWidth = width;
	_screenHeight = height;

    //if (TTF_Init() < 0)
    //    throw std::exception(TTF_GetError());

    //_font24 = TTF_OpenFont(".\\Resources\\Fonts\\arial.ttf", 24);
    //_font24 = TTF_OpenFont("E:/Projects/Doom-Nukem-CPP/Doom-Nukem/Debug/Resources/Fonts/arial.ttf", 24);

    //if (_font24 == nullptr) {
    //    std::cout << TTF_GetError();
    //    throw std::exception(TTF_GetError());
    //}

    _renderer = SDL_CreateRenderer(_window, -1, NULL);
    if (_renderer == nullptr)
        throw std::exception("Could not create renderer");

    _player = new Player();

	_worldMap = new Map();

	_textureManager = new TextureManager();

	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));
	_textureManager->load(GeneratedTextureGenerator::generateTexture(_renderer));

	//loadTextures();

	_keyboardHandler = new KeyboardHandler();

    SDL_SetRelativeMouseMode(SDL_TRUE);

}

void Game::start()
{
    _isRunning = true;
    while (_isRunning)
    {
        const auto frameStart = SDL_GetTicks();


		SDL_RenderClear(_renderer);

        handleEvents();
        update();
        render();

        const auto frameTime = SDL_GetTicks();

        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void Game::stop()
{
    _isRunning = false;
}

void Game::loadTextures()
{
	auto str = junk::ExePath();
	std::cout << "my directory is " << std::string(str.begin(), str.end()) << "\n";

	const auto base_path = std::string(str.begin(), str.end());
	
	std::vector<std::string> paths;
	paths.push_back(base_path + "\\Resources\\Textures\\purplestone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\eagle.png");
	paths.push_back(base_path + "\\Resources\\Textures\\colorstone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\bluestone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\redbrick.png");
	paths.push_back(base_path + "\\Resources\\Textures\\wood.png");
	for (const auto p : paths)
	{
		_textureManager->load(p.c_str(), _renderer);
	}
}

void Game::handleEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			_keyboardHandler->handleKeyBoardEvent(event);
			break;

		case SDL_QUIT:
			_isRunning = false;
			break;

		case SDL_MOUSEMOTION:
		{
			if (event.motion.xrel == 0) {
				break;
			}

			if (event.motion.xrel < 0) {
				_player->rotateLeft();
			}
			else {
				_player->rotateRight();
			}

			break;
		}
		default:
			break;
		}
	}

	if (_keyboardHandler->isPressed(SDL_SCANCODE_Q))
		_isRunning = false;

}

void Game::update()
{

	// handle player movement
	//_movePlayer();
	if (_keyboardHandler->isPressed(SDL_SCANCODE_W))
	{
		_player->moveForwards(_worldMap->map());
	}
	if (_keyboardHandler->isPressed(SDL_SCANCODE_S))
	{
		_player->moveBackwards(_worldMap->map());
	}
	if (_keyboardHandler->isPressed(SDL_SCANCODE_D))
	{
		_player->moveRight(_worldMap->map());
	}
	if (_keyboardHandler->isPressed(SDL_SCANCODE_A))
	{
		_player->moveLeft(_worldMap->map());
	}

	for (int x = 0; x < _screenWidth; x++)
	{
		// do the raycasting
		float cameraX = 2 * x / (float)_screenWidth - 1; //x-coordinate in camera space
		float rayDirX = _player->dirX() + _player->dirY() * cameraX;
		float rayDirY = _player->dirY() + _player->planeY() * cameraX;

		////which box of the map we're in
		int mapX = (int)_player->posX();
		int mapY = (int)_player->posY();
		int side;

		float perpWallDist = RaycastingEngine::calculatePerpWallDist(
			x, _player->posX(), _player->posY(), rayDirX, rayDirY,
			_worldMap->map(), &side, &mapX, &mapY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(_screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + _screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + _screenHeight / 2;
		if (drawEnd >= _screenHeight)
			drawEnd = _screenHeight - 1;

		//choose wall color
		//SDL_Color color = _getMapPositionToColor(mapX, mapY, side);
		//

		//texturing calculations
		int texNum = _worldMap->map()[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		int texHeight = 64;
		int texWidth = 64;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = _player->posY() + perpWallDist * rayDirY;
		else           wallX = _player->posX() + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = int(wallX * double(64));
		if (side == 0 && rayDirX > 0) texX = 64 - texX - 1;
		if (side == 1 && rayDirY < 0) texX = 64 - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - _screenHeight / 2 + lineHeight / 2) * step;


		int texY = (int)texPos & (texHeight - 1);
		//_graphicsController->setTextureVertical(_textureManager->getTexture(texNum), x, drawStart, lineHeight, texX, texY);

		SDL_Rect destRect = { x, drawStart, 1, lineHeight };
		SDL_Rect srcRect = { texX, texY, 1, 64 };
		const auto texture = _textureManager->getTexture(texNum);
		SDL_RenderCopy(_renderer, texture, &srcRect, &destRect);


		//std::vector<Uint32> texture = _textureManager->getTexture(texNum);
		//for (int y = drawStart; y < drawEnd; y++)
		//{
		//	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		//	int texY = (int)texPos & (texHeight - 1);
		//	texPos += step;

		//	Uint32 colorInt = texture[texHeight * texY + texX];
		//	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		//	//if (side == 1)
		//	//	colorInt = (colorInt >> 1) & 8355711;

		//	SDL_Color color = { 0, 0, 0, 255 };

		//	color.r = colorInt >> 24 & 0xFF;
		//	color.g = colorInt >> 16 & 0xFF;
		//	color.b = colorInt >> 8 & 0xFF;

		//	_graphicsController->setPixel(x, y, color);
		//}
		//	SDL_Color color = { 255, 0, 0, 255 };
		//_graphicsController->drawLine(x, drawStart, x, drawEnd, color);

	}
}


void Game::render()
{
    //SDL_RenderClear(_renderer);

    SDL_RenderPresent(_renderer);
}

void Game::clean()
{
    delete _player;
	delete _keyboardHandler;

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

}

