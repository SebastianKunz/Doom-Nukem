#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		_keyState[i] = false;
	}
}

KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::handleKeyBoardEvent(SDL_Event event)
{
	_keyState[event.key.keysym.scancode] = event.type == SDL_KEYDOWN;
}

bool KeyboardHandler::isPressed(SDL_Scancode scanCode)
{
	return _keyState[scanCode] == true;
}

bool KeyboardHandler::isReleased(SDL_Scancode scanCode)
{
	return _keyState[scanCode] == false;
}
