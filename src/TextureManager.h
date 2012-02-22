#pragma once

#include "Texture.h"
#include <map>

class TextureManager
{
private:

	// hashed filename to Texture object
	std::map<u32, Texture> textures;
public:
	TextureManager(void);
	~TextureManager(void);

	// Return NULL on error. These functions use GXBase to load the image
	// and will automatically build mipmaps. The image from GXBase will then
	// be destroyed as it is no longer required.
	Texture* LoadTextureFromFile(const c8* const _filename);

	Texture* GetTexture(const u32 _id);
	bool DeleteTexture(const u32 _id); // returns false if texture doesn't exist

	void Cleanup();
};