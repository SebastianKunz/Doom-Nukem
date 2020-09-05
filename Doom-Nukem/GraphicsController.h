#ifndef GRAPHICS_CONTROLLER_H
#define GRAPHICS_CONTROLLER_H

#include <SDL.h>
#include <exception>

#include <SDL_ttf.h>

namespace doom_nukem
{


class GraphicsController
{
public:
	GraphicsController(int width, int height);
	~GraphicsController();

	void present();

	void clear();

	void drawFPS(int fps);

	void drawVerticalLine(int x, int y, int height, SDL_Color color);

	void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

	void setPixel(int x, int y, SDL_Color color);

	void setTextureVertical(SDL_Surface* rawTexture, int x, int y, int height, int texX, int texY);

private:

	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;

	TTF_Font* _font24 = nullptr;
};

}
#endif // !GRAPHICS_CONTROLLER_H 
