#pragma once

#include <vector>

#include "Point.h"
#include "Defs.h"

#include "PugiXml/src/pugixml.hpp"

enum class TiledOrientation
{
	UNKNOWN,
	ORTHOGONAL,
	ISOMETRIC,
	STAGGERED
};

class TileSet
{
public:
	explicit TileSet(const pugi::xml_node& node, const std::string& directory);

private:
	uint firstGid = 0;
	std::string source = "";
	std::string name = "";
	uPoint tileSize = { 0, 0 };
	uint tileCount = 0;
	uint columns = 0;
	TiledOrientation orientation = TiledOrientation::UNKNOWN;
	uPoint size = { 0, 0 };
	std::string imageSource = "";
	uPoint sourceSize = { 0, 0 };
};
