#ifndef I_TEXTUREMANAGER_H
#define I_TEXTUREMANAGER_H

/*
* Interface for Texture loaders
*/
class ITextureManager
{
public:
	ITextureManager();
	virtual ~ITextureManager();
	
	virtual void loadTextures() = 0;

private:

};

#endif // !I_TEXTURE_MANAGER_H
