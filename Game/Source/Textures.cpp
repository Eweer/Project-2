#include "App.h"
#include "Textures.h"

#include "Defs.h"
#include "Log.h"

#include <utility>
#include "SDL_image/include/SDL_image.h"

Textures::Textures() : Module()
{
	name = "textures";
}

// Destructor
Textures::~Textures() = default;

// Called before render is available
bool Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");

	// Load support for the PNG image format
	if(int flags = IMG_INIT_PNG; (IMG_Init(flags) & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		return false;
	}

	return true;
}

// Called before the first frame
bool Textures::Start()
{
	LOG("Start textures");
	return true;
}

// Called before quitting
bool Textures::CleanUp()
{
	LOG("Freeing textures and Image library");
	textures.clear();
	IMG_Quit();
	return true;
}

int Textures::Load(std::string const &path)
{
	if (auto result = pathToInfo.find(path);
		result != pathToInfo.end())
	{
		LOG("Texture [ %s ] already loaded", path);
		result->second.second++;
		return result->second.first;
	}

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (!surface)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
		return -1;
	}

	auto texture = (
		SDL_CreateTextureFromSurface(app->GetRender(), surface)
	);

	SDL_FreeSurface(surface);

	if (texture)
	{
		// Get first available ID
		auto texIter = availableIDs.begin();
		auto texID = *texIter;

		// Add texture with key ID
		textures[texID] = (texture);

		// Add texture path/id to look up maps
		auto pairToEmplace = std::make_pair(texID, 1);
		pathToInfo[path] = pairToEmplace;
		indexToPath[texID] = path;

		// Remove the used ID from the available IDs
		availableIDs.erase(texIter);

		// If there are no more available IDs we add a new one
		if (availableIDs.empty())
		{
			availableIDs.emplace(textures.size());
		}

		LOG("Texture loaded succesfully [ %s ]", path.c_str());
		return texID;
	}
	
	LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());

	return 0;
}

void Textures::Unload(int index)
{
	if (auto result = textures.find(index);
		result != textures.end() && result->second)
	{
		auto path = indexToPath.find(index);
		auto info = pathToInfo.find(path->second);

		info->second.second--;

		if (info->second.second == 0)
		{
			SDL_DestroyTexture(result->second);
			LOG("Texture [ %s ] destroyed.", path->second);
			pathToInfo.erase(path->second);
			indexToPath.erase(index);

			// Remove map element
			textures.erase(result);

			// Add index to list of available indexes
			availableIDs.insert(index);
		}
		else
		{
			LOG("Removed reference to texture [ %s ].", path->second);
		}
	}
}

// Retrieve size of a texture
void Textures::GetSize(SDL_Texture* const texture, uint &width, uint &height) const
{
	SDL_QueryTexture(texture, nullptr, nullptr, (int*) &width, (int*) &height);
}

SDL_Texture *Textures::GetTexture(int textureID) const
{
	if (auto result = textures.find(textureID);
		result != textures.end())
	{
		return result->second;
	}
	return nullptr;
}
