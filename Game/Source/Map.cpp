#include "Map.h"
#include "App.h"
#include "Render.h"

#include "Log.h"

#include "SDL_image/include/SDL_image.h"

#include <ranges>


Map::Map() = default;

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

	pugi::xml_node map = mapFile.child("map");

	if (!map)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		return false;
	}

	if (StrEquals(map.attribute("orientation").as_string(),"orthogonal"))
		orientation = MapTypes::MAPTYPE_ORTHOGONAL;
	else if (StrEquals(map.attribute("orientation").as_string(),"isometric"))
		orientation = MapTypes::MAPTYPE_ISOMETRIC;
	else if (StrEquals(map.attribute("orientation").as_string(), "staggered"))
		orientation = MapTypes::MAPTYPE_STAGGERED;
	else
	{
		LOG("Error parsing xml file: 'orientation' attribute is unknown.");
		return false;
	}

	size.x = map.attribute("height").as_uint();
	size.y = map.attribute("width").as_uint();
	tileSize.x = map.attribute("tileheight").as_uint();
	tileSize.y = map.attribute("tilewidth").as_uint();

	for (auto const& child : mapFile.child("map"))
	{
		if (StrEquals(child.name(), "tileset"))
		{
			tilesets.emplace_back(child, directory);
		}
		else if (StrEquals(child.name(), "layer"))
		{
			drawOrder.emplace_back(LayerType::TILE_LAYER, tileLayers.size());
			tileLayers.emplace_back(child);
		}
		else if (StrEquals(child.name(), "objectgroup"))
		{
			// If the name of the ObjectGroup is Events use 
			// the EventManager to create and store them
			if (StrEquals("Layer of Events", child.attribute("class").as_string()))
			{
				drawOrder.emplace_back(LayerType::EVENT_LAYER, eventManager.GetEventLayerSize());
				eventManager.CreateEvent(child);
			}
			else 
			{
				drawOrder.emplace_back(LayerType::OBJECT_LAYER, objectLayers.size());
				objectLayers.emplace_back(child);
			}
		}
		else
		{
			LOG("Error parsing xml file: '%s' tag not implemented.", child.name());
			continue;
		}
	}

	eventManager.Initialize();

	return true;
}

void Map::Draw()
{
	for (auto const& [type, index] : drawOrder)
	{
		using enum LayerType;
		switch (type)
		{
			case TILE_LAYER:
				DrawTileLayer(tileLayers[index]);
				break;
			case EVENT_LAYER:
				while(DrawObjectLayer(index));
				break;
			case OBJECT_LAYER:
				break;
		}
	}
}

bool Map::DrawObjectLayer(int index)
{
	auto [gid, pos, keepDrawing] = eventManager.GetDrawEventInfo(index);
	
	if (gid > 0) DrawTile(gid, pos);

	return keepDrawing;
}

void Map::DrawTileLayer(const MapLayer& layer) const
{
	for (uint x = 0; x < layer.GetSize().x; x++)
	{
		for (uint y = 0; y < layer.GetSize().y; y++)
		{
			uint gid = layer.GetTileGid(x, y);

			if (gid == 0) continue;

			DrawTile(gid, MapToWorld(x, y));
		}
	}
}

void Map::DrawTile(uint gid, uPoint pos) const
{
	auto result = std::ranges::find_if(
		tilesets,
		[gid](const TileSet& t) { return t.ContainsGid(gid); }
	);

	if (result == tilesets.end())
	{
		LOG("Tileset for tile gid %s not found.", gid);
		return;
	}

	SDL_Rect r = (*result).GetTileRect(gid);

	app->render->DrawTexture((*result).GetTexture(), pos.x, pos.y, &r);
}

// Translates x,y coordinates from map positions to world positions
uPoint Map::MapToWorld(uint x, uint y) const
{
	return { x * tileSize.x, y * tileSize.y };
}

// Translates x coordinates from map positions to world positions
uint Map::MapXToWorld(uint x) const
{
	return x * tileSize.x;
}

// Translates x,y coordinates from map positions to world positions
uPoint Map::MapToWorld(uPoint position) const
{
	return { position.x * tileSize.x, position.y * tileSize.y };
}

int Map::GetWidth() const { return size.x; };
int Map::GetHeight() const { return size.y; };
int Map::GetTileWidth() const { return tileSize.x; };
int Map::GetTileHeight() const { return tileSize.y; };
int Map::GetTileSetSize() const { return tilesets.size(); };
