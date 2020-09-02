#ifndef FILE_TEXTURE_MANAGER_H
# define FILE_TEXTURE_MANAGER_H
#include "ITextureManager.h"
#include <vector>
#include <string>
#include <SDL.h>
#include <memory>
#include <SDL_image.h>

class FileTextureManager : public ITextureManager
{
public:
	FileTextureManager();
	FileTextureManager(std::vector<std::string> filePaths);
	~FileTextureManager();

	void loadTextures() override;

	SDL_Surface *getTexture(int idx);

private:

	std::vector<std::string> _filePaths;

	std::vector<SDL_Surface*> _textures;

};

#endif // !FILE_TEXTURE_MANAGER_H
