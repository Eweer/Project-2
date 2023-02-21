#pragma once

#include "GuiButton.h"
#include "GuiElement.h"
#include "Textures.h"

#include <memory>
#include <vector>

class GuiScreen
{
public:

	explicit GuiScreen(pugi::xml_node const &node);

	bool IsMouseHovering() const;

	void StartGame() const;

private:
	uPoint position = { 0, 0 };
	uPoint size = { 0, 0 };
	SDL_Color color = { 255,255,255,50};

	bool bIsActive = false;

	std::shared_ptr<SDL_Texture> background = nullptr;
	std::vector<std::unique_ptr<GuiElement>> widgets;
};

