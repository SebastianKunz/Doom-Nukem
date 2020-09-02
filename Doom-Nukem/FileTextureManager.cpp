#include "FileTextureManager.h"
#include <iostream>

FileTextureManager::FileTextureManager(std::vector<std::string> filePaths)
{
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::exception(IMG_GetError());

	_filePaths = filePaths;
}

FileTextureManager::~FileTextureManager()
{
}

void FileTextureManager::loadTextures()
{
	for (auto const& path : _filePaths) {
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (!loadedSurface) {
			throw std::exception(IMG_GetError());
		}

		_textures.push_back(loadedSurface);
	}
}

SDL_Surface* FileTextureManager::getTexture(int idx)
{
	if (idx >= 0 && idx < _textures.size())
		return _textures[idx];


	return nullptr;
}

