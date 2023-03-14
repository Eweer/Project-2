#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Event_Base.h"

#include <memory>
#include <vector>

struct TileInfo;

class EventManager
{
public:

	EventManager();

	// Destructor
	~EventManager();

	// ------ Event
	// --- Constructors
	bool CreateEvent(pugi::xml_node const &node = pugi::xml_node());

	int GetEventLayerSize() const;
private:
	std::vector<std::unique_ptr<Event_Base>> events;
};


#endif // __ENTITYMANAGER_H__
