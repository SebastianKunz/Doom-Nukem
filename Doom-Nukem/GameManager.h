#ifndef GAME_MANAGER_H

#include <SDL.h>
#include "KeyboardHandler.h"
#include "Player.hpp"
#include "RaycastingEngine.hpp"
#include <chrono>
#include "GraphicsController.hpp"
#include <memory>

class GameManager
{
public:
	GameManager& getInstance();

	void start();

	//GameManager(GameManager const&) = delete;

	//void operator=(GameManager const&) = delete;

	~GameManager();


	GameManager();


private:
	

	void _movePlayer();

	bool _done = false;

	KeyboardHandler _keyboardHandler;
	Player _player;
	std::unique_ptr<GraphicsController> _graphicsController;

	int** _worldMap;

	std::chrono::system_clock::time_point _time; //time of current frame
	std::chrono::system_clock::time_point _oldTime; //time of previous frame
	std::chrono::duration<double> _frameTime;

	int _screenWidth = 640 * 2;
	int _screenHeight = 480 * 2;

};

#endif // !GAME_MANAGER_H
