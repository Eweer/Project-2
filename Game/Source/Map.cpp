#include "Map.h"

#include "Log.h"

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
	}
	return true;
}
