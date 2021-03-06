#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <SDL.h>

namespace doom_nukem
{


class KeyboardHandler
{
public:
	KeyboardHandler();
	~KeyboardHandler();

	void handleKeyBoardEvent(SDL_Event event);

	bool isPressed(SDL_Scancode scanCode);

	bool isReleased(SDL_Scancode scanCode);

private:
	
	bool _keyState[SDL_NUM_SCANCODES];

};

}

#endif // !KEYBOARD_HANDLER_H


