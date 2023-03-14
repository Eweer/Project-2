#include "EventManager.h"
#include "App.h"

#include "Event_Chest.h"
#include "Event_Teleport.h"

#include "Log.h"

EventManager::EventManager() = default;

// Destructor
EventManager::~EventManager() = default;

bool EventManager::CreateEvent(pugi::xml_node const& node)
{
	for (auto const& child : node.children("object"))
	{
		std::unique_ptr<Event_Base> event = nullptr;

		if (StrEquals("Event Chest", child.attribute("type").as_string()))
		{
			event = std::make_unique<Event_Chest>();
		}
		else if (StrEquals("Event Teleport", child.attribute("type").as_string()))
		{
			event = std::make_unique<Event_Teleport>();
		}

		if (!event)
		{
			LOG("Event \"%s\" not yet implemented.", child.attribute("type").as_string());
			continue;
		}

		event->Initialize(child);
		events.push_back(std::move(event));
	}
	return true;
}

int EventManager::GetEventLayerSize() const
{
	return events.size();
}


