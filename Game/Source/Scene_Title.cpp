#include "Scene_Title.h"

#include "Log.h"

bool Scene_Title::isReady()
{
	return false;
}

void Scene_Title::Load(std::string const& path, LookUpXMLNodeFromString const& info, Window_Factory const &windowFactory)
{
	auto sceneHash = info.find("Title");
	if (sceneHash == info.end())
	{
		LOG("Title scene not found in XML.");
		return;
	}

	auto scene = sceneHash->second;

	for (auto const& window : scene.children("window"))
	{
		if (auto result = windowFactory.CreateWindow(window.attribute("name").as_string());
			result != nullptr)
		{
			windows.push_back(std::move(result));
		}
	}
}

void Scene_Title::Start()
{
}

void Scene_Title::Update()
{
	for (auto const& elem : windows)
	{
		elem->Draw();
	}
}
