#pragma once

#include "Point.h"
#include "Defs.h"

#include <vector>

#include "PugiXml/src/pugixml.hpp"
#include "SDL_image/include/SDL_image.h"

enum class MapOrientation
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

	uint ContainsGid(uint gid) const
	{
		return gid >= firstGid && gid < firstGid + tileCount;
	}

	SDL_Rect GetTileRect(uint gid) const
	{
		SDL_Rect rect = { 0 };
		uint relativeIndex = gid - firstGid;

		rect.w = tileSize.x;
		rect.h = tileSize.y;
		rect.x = margin + (tileSize.x + spacing) * (relativeIndex % columns);
		rect.y = margin + (tileSize.y + spacing) * (relativeIndex / columns);

		return rect;
	}

	SDL_Texture* GetTexture() const
	{
		return texture;
	}

private:
	uint firstGid = 0;
	std::string source = "";
	std::string name = "";
	uPoint tileSize = { 0, 0 };
	uint tileCount = 0;
	uint columns = 0;
	MapOrientation orientation = MapOrientation::UNKNOWN;
	uPoint size = { 0, 0 };
	std::string imageSource = "";
	uPoint sourceSize = { 0, 0 };
	SDL_Texture *texture = nullptr;

	uint margin = 0;
	uint spacing = 0;
};
