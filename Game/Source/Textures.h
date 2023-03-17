#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Module.h"

#include <map>
#include <memory>
#include <set>
#include <functional>
#include "SDL_image/include/SDL_image.h"


class Textures : public Module
{
public:

	Textures();

	// Destructor
	~Textures() final;

	// Called before render is available
	bool Awake(pugi::xml_node&) final;

	// Called before the first frame
	bool Start() final;

	// Called before quitting
	bool CleanUp() final;

	// Load Texture
	int Load(std::string const &path);
	void Unload(int index);
	void GetSize(SDL_Texture* const texture, uint& width, uint& height) const;
	SDL_Texture* GetTexture(int textureID) const;

	// Path to pair<Index, references> look up table
	std::unordered_map<std::string, std::pair<int, int>, StringHash, std::equal_to<>> pathToInfo;
	std::unordered_map<int, std::string> indexToPath;
	std::map<int, SDL_Texture*> textures;
	std::set<int> availableIDs{ 0 };
};


#endif // __TEXTURES_H__