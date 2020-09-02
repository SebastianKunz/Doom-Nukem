#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL.h>
#include <iostream>
#include "KeyboardHandler.h"
#include "Player.h"
#include "RaycastingEngine.h"
#include <chrono>
#include "GraphicsController.h"
#include <memory>
#include <thread>
#include <vector>
#include "GeneratedTextureManager.h"
#include "FileTextureManager.h"

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

	SDL_Color _getMapPositionToColor(int mapX, int mapY, bool side);

	std::vector<uint32_t> _getMapPositionToGenTexture(int mapX, int mapY, bool side);

	void _waitToFitFPS();

	void _pollEvents();

	void _calculateFps();

	bool _done = false;

	KeyboardHandler _keyboardHandler;
	Player _player;
	std::unique_ptr<GraphicsController> _graphicsController;
	//std::unique_ptr<ITextureManager> _textureManager;
	//std::unique_ptr<GeneratedTextureManager> _textureManager;

	// TODO: should allow to switch between texture and generated textures renderer
	std::unique_ptr<FileTextureManager> _textureManager;

	int** _worldMap;

	std::chrono::system_clock::time_point _start; 
	std::chrono::system_clock::time_point _end;

	std::chrono::system_clock::time_point _time; //time of current frame
	std::chrono::system_clock::time_point _oldTime; //time of previous frame
	std::chrono::duration<double> _frameTime;

	int _fps = 0;

	int _screenWidth = 640 * 2;
	int _screenHeight = 480 * 2;

	int _frameCount = 0;
	float _wantedFps = 150;
};

#endif // !GAME_MANAGER_H
