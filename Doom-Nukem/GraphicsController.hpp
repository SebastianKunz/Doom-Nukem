#ifndef RENDERER_H

#include <SDL.h>
#include <exception>

class GraphicsController
{
public:
	GraphicsController(int width, int height);
	~GraphicsController();

	void present();

	void clear();

	void drawVerticalLine(int x, int y, int height, SDL_Color color);

	void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

private:

	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
};

#endif // !RENDERER_H
