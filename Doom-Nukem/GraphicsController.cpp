#include "GraphicsController.h"
#include <iostream>
#include <string>

namespace doom_nukem
{


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
    if (TTF_Init() < 0)
        throw std::exception(TTF_GetError());

    //_font24 = TTF_OpenFont(".\\Resources\\Fonts\\arial.ttf", 24);
    _font24 = TTF_OpenFont("E:/Projects/Doom-Nukem-CPP/Doom-Nukem/Debug/Resources/Fonts/arial.ttf", 24);

    if (_font24 == nullptr) {
        std::cout << TTF_GetError();
        throw std::exception(TTF_GetError());
    }

    _renderer = SDL_CreateRenderer(_window, -1, NULL);
    if (_window == nullptr) {
        throw std::exception("Could not create window");
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);
}

GraphicsController::~GraphicsController()
{
    TTF_CloseFont(_font24);
    TTF_Quit();
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

void GraphicsController::drawFPS(int fps)
{
    SDL_Color color = { 0, 255, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font24, std::to_string(fps).c_str(), color);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 45; // controls the width of the rect
    Message_rect.h = 45; // controls the height of the rect

    SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

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

void GraphicsController::setPixel(int x, int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(_renderer, x, y);
}

void GraphicsController::setTextureVertical(SDL_Surface *rawTexture, int x, int y, int height, int texX, int texY)
{
    if (rawTexture == nullptr)
        return;

    //std::cout << "Drawing:\n" << "x: " << x << "y: " << y << "height: " << height << "texX: " << texX << std::endl;
    SDL_Rect destRect = { x, y, 1, height };
    SDL_Rect srcRect = { texX, texY, 1, 64 };
    auto texture = SDL_CreateTextureFromSurface(_renderer, rawTexture);
    SDL_RenderCopy(_renderer, texture, &srcRect, &destRect);
    SDL_DestroyTexture(texture);
}
}
