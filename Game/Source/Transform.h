#pragma once

#include "Point.h"

#include "PugiXml/src/pugixml.hpp"

class Transform
{
public:
	iPoint GetPosition() const { return position; };
	iPoint GetSize() const { return size; };

protected:
	void Initialize(pugi::xml_node const& node)
	{
		position = { node.attribute("x").as_int(), node.attribute("y").as_int() };
		size = { node.attribute("width").as_int(), node.attribute("height").as_int() };

	}
private:
	iPoint position = { 0 };
	iPoint size = { 0 };
};

