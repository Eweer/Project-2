#ifndef __WINDOW_BASE_H__
#define __WINDOW_BASE_H__

#include "Window_Base.h"

#include <stack>
#include <memory>

using LookUpXMLNodeFromString = std::unordered_map<std::string, pugi::xml_node, StringHash, std::equal_to<>>;

class Scene_Base
{
public:
	Scene_Base() = default;
	virtual ~Scene_Base() = default;

	virtual bool isReady() = 0;
	virtual void Load(
		std::string const& path,
		LookUpXMLNodeFromString const &info,
		LookUpXMLNodeFromString const &windowInfo
	) = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;

	bool bActive = false;
	// TODO Fade-in/Fade-out variables (colour, duration)
	std::stack<std::unique_ptr<Window_Base>> windows;

};


#endif __WINDOW_BASE_H__