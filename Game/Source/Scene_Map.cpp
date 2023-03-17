#include "Scene_Map.h"

#include "Log.h"

bool Scene_Map::isReady()
{
	return true;
}

void Scene_Map::Load(std::string const& path, LookUpXMLNodeFromString const& info, Window_Factory const& windowFactory)
{
	// Load map
	currentMap = "Base";

	if (std::string mapToLoad = currentMap + ".tmx";
		!map.Load(path, mapToLoad))
	{
		LOG("Map %s couldn't be loaded.", mapToLoad);
	}
}

void Scene_Map::Start()
{
}

void Scene_Map::Draw()
{
	map.Draw();
}

int Scene_Map::Update()
{
	return 0;
}

int Scene_Map::CheckNextScene()
{
	return 0;
}
