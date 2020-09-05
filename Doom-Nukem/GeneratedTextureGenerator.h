#ifndef GENERATED_TEXTURE_GENERATOR_H
#define GENERATED_TEXTURE_GENERATOR

#include <vector>
#include "SDL.h"

namespace doom_nukem
{


class GeneratedTextureGenerator
{
public:
	GeneratedTextureGenerator();
	~GeneratedTextureGenerator();
	
	static SDL_Texture* generateTexture(SDL_Renderer *renderer);


private:
};

}
#endif // !GENERATED_TEXTURE_MANAGER_H

