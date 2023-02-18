#include "TileSet.h"

#include "Log.h"

TileSet::TileSet(const pugi::xml_node& node, const std::string& directory) :
	firstGid(node.attribute("firstgid").as_uint()),
	source(node.attribute("source").as_string())
{
	pugi::xml_document tileSetFile;
	if (pugi::xml_parse_result parseResult = tileSetFile.load_file((directory + source).c_str());
		!parseResult)
	{
		LOG("TileSet file for %s parsing error: %s", source, parseResult.description());
		return;
	}
	
	pugi::xml_node currentNode = tileSetFile.child("tileset");

	name = currentNode.attribute("name").as_string();
	tileSize = { currentNode.attribute("tilewidth").as_uint(), currentNode.attribute("tileheight").as_uint() };
	tileCount = currentNode.attribute("tilecount").as_uint();
	columns = currentNode.attribute("columns").as_uint();

	currentNode = currentNode.child("grid");
	if (currentNode.empty())
	{
		// Default values if grid child doesn't exist
		orientation = TiledOrientation::ORTHOGONAL;
		size = tileSize;
	}
	else
	{
		// TODO read XML attribute
		orientation = TiledOrientation::ORTHOGONAL;
		size = { currentNode.attribute("width").as_uint(), currentNode.attribute("height").as_uint() };
	}

	currentNode = currentNode.next_sibling("image");
	imageSource = currentNode.attribute("source").as_string();
	sourceSize = { currentNode.attribute("width").as_uint(), currentNode.attribute("height").as_uint() };
}

