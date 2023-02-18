#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "TileSet.h"
#include "MapLayer.h"

#include "Defs.h"

#include <variant>				//std::variant
#include <unordered_map>		//std::unordered_map
#include <vector>				//std::vector

#include "PugiXml/src/pugixml.hpp"

using XML_Property_t = std::variant<int, bool, float, std::string>;
using XML_Properties_Map_t = std::unordered_map<std::string, XML_Property_t, StringHash, std::equal_to<>>;

enum class MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

class Map : public Module
{
public:

	Map();

	// Destructor
	~Map() final;

	bool Load(const std::string& directory, const std::string& level);

	// Called each loop iteration
	void Draw() const {};

	// Called before quitting
	bool CleanUp() final { return true; };

	// Load new map
	bool Load() {
		return true;
	};

	int GetWidth() const { return 24*16; };
	int GetHeight() const { return 24 * 16; };

	int GetTileWidth() const { return 16; };
	int GetTileHeight() const { return 16; };

	int GetTileSetSize() const {
		return 40;
	};

private:
	std::vector<TileSet> tilesets;
};

#endif // __MAP_H__
