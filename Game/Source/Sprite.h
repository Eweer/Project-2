#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Point.h"

#include "PugiXml/src/pugixml.hpp"

class Sprite
{
public:
	int GetGid() const { return gid; };
	int GetTextureID() const { return textureID; };

protected:
	void Initialize(pugi::xml_node const& node)
	{
		textureID = node.attribute("id").as_int();
		gid = node.attribute("gid").as_uint();
	};

private:

	int textureID = -1;
	int gid = -1;

};

#endif //__SPRITE_H__
