#ifndef __WINDOW_LIST_H__
#define __WINDOW_LIST_H__

#include "Window_Base.h"
class Window_List : public Window_Base
{
public:
	explicit Window_List(pugi::xml_node const& node);
	void InitializeFunctionPointerMap() override;
};

#endif __WINDOW_LIST_H__