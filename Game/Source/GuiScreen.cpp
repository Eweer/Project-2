#include "GuiScreen.h"

GuiScreen::GuiScreen(pugi::xml_node const& node) :
	position({ node.attribute("x").as_uint(), node.attribute("y").as_uint() }),
	size({ node.attribute("width").as_uint(), node.attribute("height").as_uint() })
{
	for (auto const& child : node)
	{
		if (child.name() == "screen")
		{
			uPoint pos = { child.attribute("x").as_uint(), node.attribute("y").as_uint() };
			uPoint s = { child.attribute("width").as_uint(), node.attribute("height").as_uint() };
			std::string const text = child.attribute("text").as_string();
			widgets.emplace_back(std::make_unique<GuiButton>(pos, s, text, &StartGame));
		}
	}
}

bool GuiScreen::IsMouseHovering() const
{
	uPoint mousePos = app->input->GetUnsignedMousePosition();

	if (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
		mousePos.y >= position.y && mousePos.y <= position.y + size.y)
	{
		return true;
	}

	return false;
}

void GuiScreen::StartGame()
{
}

