#include "Map.h"
#include "App.h"
#include "Render.h"

#include "Log.h"

#include "SDL_image/include/SDL_image.h"
Map::Map() : Module()
{
	name = "map";
}

// Destructor
Map::~Map() = default;

bool Map::Load(const std::string& directory, const std::string& level)
{
	pugi::xml_document mapFile;

	if (auto result = mapFile.load_file((directory + level).c_str()); !result)
	{
		LOG("Could not load map xml file %s. pugi error: %s", directory + level, result.description());
		return false;
	}

	for (auto const& child : mapFile.child("map"))
	{
		if (StrEquals(child.name(), "tileset"))
		{
			tilesets.emplace_back(child, directory);
		}
		else if (StrEquals(child.name(), "layer"))
		{
			tileLayers.emplace_back(child);
		}
		else if (StrEquals(child.name(), "objectgroup"))
		{
			objectLayers.emplace_back(child);
		}
	}
	return true;
}

void Map::Draw() const
{
	for (MapLayer layer : tileLayers)
	{
		for (uint x = 0; x < layer.GetSize().x; x++)
		{
			for (uint y = 0; y < layer.GetSize().y; y++)
			{
				uint gid = layer.GetTileGid(x, y);
				
				if (gid <= 0) continue;

				uint tileset = 0;
				while (tileset < tilesets.size() && !tilesets[tileset].ContainsGid(gid))
					tileset++;

				if (tileset >= tilesets.size())
				{
					LOG("Tileset for tile gid %s not found.", gid);
					continue;
				}
				SDL_Rect r = tilesets[tileset].GetTileRect(gid);
				uPoint pos = MapToWorld(x, y);

				app->render->DrawTexture(tilesets[tileset].GetTexture(), pos.x, pos.y, &r);
			}
		}
	}
}

// Translates x,y coordinates from map positions to world positions
uPoint Map::MapToWorld(uint x, uint y) const
{
	return { x * 16, y * 16 };
}

// Translates x,y coordinates from map positions to world positions
uint Map::MapXToWorld(uint x) const
{
	return x * 16;
}

// Translates x,y coordinates from map positions to world positions
uPoint Map::MapToWorld(uPoint position) const
{
	return { position.x * 16, position.y * 16 };
}