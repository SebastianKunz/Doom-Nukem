#include "GraphicsController.hpp"

GraphicsController::GraphicsController(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::exception("Failed to init SDL");
    }
    _window = SDL_CreateWindow(
        "Doom Nukem by Skunz",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    _renderer = SDL_CreateRenderer(_window, -1, NULL);
    if (_window == nullptr) {
        throw std::exception("Could not create window");
    }
}

GraphicsController::~GraphicsController()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void GraphicsController::present()
{
    SDL_RenderPresent(_renderer);
}

void GraphicsController::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void GraphicsController::drawVerticalLine(int x, int y, int height, SDL_Color color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer, x, y, x, y + height);
}

void GraphicsController::drawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}
