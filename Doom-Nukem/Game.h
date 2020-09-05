#ifndef GAME_H
# define GAME_H

#include "SDL.h"
#include <exception>
#include <SDL_ttf.h>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "TextureManager.h"
#include "KeyboardHandler.h"

namespace doom_nukem
{
class Game
{
public:
	Game();

	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height);

	void start();
	void stop();

	bool running() { return _isRunning; }

private:

	void loadTextures();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool _isRunning;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	Player* _player;

	int _screenWidth;
	int _screenHeight;

	Map* _worldMap;

	TextureManager* _textureManager;

	KeyboardHandler* _keyboardHandler;

};

}


#endif