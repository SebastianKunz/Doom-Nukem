#include "GameManager.h"

GameManager& GameManager::getInstance() {
	static GameManager instance;
	
	return instance;
}

void GameManager::start()
{
	_done = false;
	while (!_done) {

		_start = std::chrono::system_clock::now();

		std::chrono::duration<double, std::milli> workTime = _start - _end;

		if (workTime.count() < ((1.0f / _wantedFps) * 1000.0f))
		{
			std::chrono::duration<double, std::milli> delta_ms((1.0f / _wantedFps) * 1000.0f - workTime.count());
			auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
			std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
		}

		_end = std::chrono::system_clock::now();

		// poll events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                _keyboardHandler.handleKeyBoardEvent(event);

			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					  _done = true;
					  break;
				  }
			  }
			if (event.type == SDL_QUIT)
				_done = true;
		}

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
			if (side == 1) {
				color.r /= 2;
				color.g /= 2;
				color.b /= 2;
			}
			
			//_graphicsController->drawVerticalLine(x, drawStart, drawEnd - drawStart, color);
			_graphicsController->drawLine(x, drawStart, x, drawEnd, color);
		}

		auto oldTime = _time;

        _time = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(_time - _oldTime).count();
		if (elapsed >= 1) {
			_fps = _frameCount / elapsed;
			_oldTime = _time;
			_frameCount = 0;
		}

		_frameTime = _time - oldTime;

		float moveSpeed = _frameTime.count() * 5.0f; //the constant value is in squares/second
		float rotSpeed = _frameTime.count() * 3.0f; //the constant value is in radians/second

		_player.setMoveSpeed(moveSpeed);
		_player.setRotSpeed(rotSpeed);
		
		_graphicsController->drawFPS(_fps);
		_graphicsController->present();
		_graphicsController->clear();
		_frameCount++;
	}
}

GameManager::GameManager() {
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
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

	_graphicsController = std::make_unique<GraphicsController>
		(_screenWidth, _screenHeight);
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
		_player.rotateRight(_worldMap);
	}
	if (_keyboardHandler.isPressed(SDL_SCANCODE_A))
	{
		_player.rotateLeft(_worldMap);
	}
}

