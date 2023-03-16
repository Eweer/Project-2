#include "Scene_Title.h"

#include "Window_List.h"

#include "Log.h"

bool Scene_Title::isReady()
{
	return false;
}

void Scene_Title::Load(std::string const& path, LookUpXMLNodeFromString const& info, LookUpXMLNodeFromString const& windowInfo)
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
		auto windowHash = windowInfo.find(window.attribute("name").as_string());
		if (windowHash == windowInfo.end())
		{
			LOG("Window information for %s not found in XML.", window.attribute("name").as_string());
			continue;
		}

		if (StrEquals("List", windowHash->second.attribute("class").as_string()))
		{
			if (StrEquals("Base", windowHash->second.attribute("type").as_string()))
			{
				windows.emplace(std::make_unique<Window_List>(windowHash->second));
			}
		}
	}
}

void Scene_Title::Start()
{
}

void Scene_Title::Update()
{
}
