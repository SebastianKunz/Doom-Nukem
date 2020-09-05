#include "GameManager.h"

#include <windows.h>
#include <string>
#include <iostream>



std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

namespace doom_nukem
{


GameManager& GameManager::getInstance() {
	static GameManager instance;
	
	return instance;
}

void GameManager::start()
{
	_done = false;
	while (!_done) {

		_waitToFitFPS();

		// poll events
		_pollEvents();

		_done = _keyboardHandler.isPressed(SDL_SCANCODE_ESCAPE);

		// handle player movement
		_movePlayer();

		for (int x = 0; x < _screenWidth; x++)
		{
			// do the raycasting
			float cameraX = 2 * x / (float)_screenWidth - 1; //x-coordinate in camera space
			float rayDirX = _player.dirX() + _player.dirY() * cameraX;
			float rayDirY = _player.dirY() + _player.planeY() * cameraX;

			////which box of the map we're in
			int mapX = (int)_player.posX();
			int mapY = (int)_player.posY();
			int side;

			float perpWallDist = RaycastingEngine::calculatePerpWallDist(
				x, _player.posX(), _player.posY(), rayDirX, rayDirY,
				_worldMap, &side, &mapX, &mapY);

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
			int texNum = _worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

			int texHeight = 64;
			int texWidth = 64;

			//calculate value of wallX
			double wallX; //where exactly the wall was hit
			if (side == 0) wallX = _player.posY() + perpWallDist * rayDirY;
			else           wallX = _player.posX() + perpWallDist * rayDirX;
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

		auto oldTime = _time;

		_calculateFps();

		_frameTime = _time - oldTime;

		float moveSpeed = _frameTime.count() * 5.0f; //the constant value is in squares/second
		float rotSpeed = _frameTime.count() * 1.0f; //the constant value is in radians/second

		_player.setMoveSpeed(moveSpeed);
		_player.setRotSpeed(rotSpeed);
		
		_graphicsController->drawFPS(_fps);
		_graphicsController->present();
		_graphicsController->clear();
		_frameCount++;
	}
}

GameManager::GameManager()  {
	int worldMap[24][24] =
	{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	_worldMap = new int* [24];

	for (int i = 0; i < 24; i++) {
		_worldMap[i] = new int[24];
		for (int k = 0; k < 24; k++) {
			_worldMap[i][k] = worldMap[i][k];
		}
	}

	_graphicsController = std::make_unique<GraphicsController>(_screenWidth, _screenHeight);


	
	auto str = ExePath();
	std::cout << "my directory is " << std::string(str.begin(), str.end()) << "\n";

	const auto base_path = std::string(str.begin(), str.end());
	
	std::vector<std::string> paths;
	paths.push_back(base_path + "\\Resources\\Textures\\purplestone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\eagle.png");
	paths.push_back(base_path + "\\Resources\\Textures\\colorstone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\bluestone.png");
	paths.push_back(base_path + "\\Resources\\Textures\\redbrick.png");
	paths.push_back(base_path + "\\Resources\\Textures\\wood.png");
	//paths.push_back("Resources\\Textures\\eagle.png");
	//paths.push_back("Resources/Textures/colorstone.png");
	//paths.push_back("Resources/Textures/bluestone.png");
	//paths.push_back("Resources/textures/redbrick.png");
	//paths.push_back("Resources/textures/wood.png");

	//try
	//{
	//	_textureManager = std::make_unique<FileTextureManager>(paths);
	//	//_textureManager = std::make_unique<GeneratedTextureManager>();
	//	_textureManager->loadTextures();
	//}
	//catch (const std::exception& e)
	//{
	//	std::cout << e.what() << std::endl;
	//}
}
GameManager::~GameManager() {}

void GameManager::_movePlayer()
{
	if (_keyboardHandler.isPressed(SDL_SCANCODE_W))
	{
		_player.moveForwards(_worldMap);
	}
	if (_keyboardHandler.isPressed(SDL_SCANCODE_S))
	{
		_player.moveBackwards(_worldMap);
	}
	if (_keyboardHandler.isPressed(SDL_SCANCODE_D))
	{
		_player.moveRight(_worldMap);
	}
	if (_keyboardHandler.isPressed(SDL_SCANCODE_A))
	{
		_player.moveLeft(_worldMap);
	}
}

SDL_Color GameManager::_getMapPositionToColor(int mapX, int mapY, bool side)
{
	SDL_Color color = { 0, 0, 0, 255 };
	switch (_worldMap[mapX][mapY])
	{
	case 1:
		color.r = 255;
		break; //red
	case 2:  color.g = 255;  break; //green
	case 3:  color.b = 255;   break; //blue
	case 4:  color.r = 0; color.g = 255; color.b = 255;;  break; //white
	default: color.r = 255; color.g = 255;  color.b = 255;; break; //yellow
	}
	//give x and y sides different brightness
	if (side) {
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
	}

	return color;
}

std::vector<uint32_t> GameManager::_getMapPositionToGenTexture(int mapX, int mapY, bool side)
{
	return std::vector<uint32_t>();
}

void GameManager::_waitToFitFPS()
{
	_start = std::chrono::system_clock::now();

	std::chrono::duration<double, std::milli> workTime = _start - _end;

	if (workTime.count() < ((1.0f / _wantedFps) * 1000.0f))
	{
		std::chrono::duration<double, std::milli> delta_ms((1.0f / _wantedFps) * 1000.0f - workTime.count());
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
	}

	_end = std::chrono::system_clock::now();
}

void GameManager::_pollEvents()
{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
                _keyboardHandler.handleKeyBoardEvent(event);

			case SDL_QUIT:
				_done = true;
			case SDL_MOUSEMOTION:
			{
				if (event.motion.xrel == 0) {
					break;
				}

				if (event.motion.xrel < 0) {
					_player.rotateLeft();
				}
				else {
					_player.rotateRight();
				}

				break;
			}
			default:
				break;
			}
		}
}

void GameManager::_calculateFps()
{
	_time = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(_time - _oldTime).count();
	if (elapsed >= 1) {
		_fps = _frameCount / elapsed;
		_oldTime = _time;
		_frameCount = 0;
	}
}

}
