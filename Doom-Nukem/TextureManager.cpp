#include "TextureManager.h"

namespace doom_nukem {


TextureManager::TextureManager() : _nextId(0)
{
}

TextureManager::~TextureManager()
{
	for (const auto tex : _textures)
	{
		SDL_DestroyTexture(tex);
	}
}

int TextureManager::load(SDL_Texture* texture)
{
	if (!texture)
		return -1;

	_textures.push_back(texture);

	return _nextId++;
}

int TextureManager::load(const char *path, SDL_Renderer* renderer)
{
	SDL_Surface* tmpSurface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	_textures.push_back(tex);

	return _nextId++;
}

SDL_Texture* TextureManager::getTexture(int id)
{
	if (id >= 0 && id < _textures.size())
		return _textures[id];

	return nullptr;
}

}
