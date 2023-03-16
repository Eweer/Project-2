#include "Window_List.h"

Window_List::Window_List(pugi::xml_node const& node) : Window_Base(node)
{
	CreateButtons(node);
}

void Window_List::InitializeFunctionPointerMap()
{
}

