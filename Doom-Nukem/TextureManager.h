#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL.h"
#include <SDL_image.h>
#include <vector>

namespace doom_nukem {


/*
* Loads Textures and holds them in a vector
*/
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	int load(SDL_Texture* texture);

	int load(const char* path, SDL_Renderer* renderer);

	SDL_Texture* getTexture(int id);



private:

	std::vector<SDL_Texture*> _textures;

	int _nextId;

};

}

#endif // !TEXTURE_MANAGER_H
