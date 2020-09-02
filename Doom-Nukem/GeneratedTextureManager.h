#ifndef GENERATED_TEXTURE_MANAGER_H
#define GENERATED_TEXTURE_MANAGER_H

#include "ITextureManager.h"
#include <vector>
#include <SDL_stdinc.h>

class GeneratedTextureManager : public ITextureManager
{
public:
	GeneratedTextureManager();
	~GeneratedTextureManager();

	void loadTextures() override;

	std::vector<Uint32> getTexture(int idx);

private:
	std::vector<Uint32> texture[8];
};

#endif // !GENERATED_TEXTURE_MANAGER_H

