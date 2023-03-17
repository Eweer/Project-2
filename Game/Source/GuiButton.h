#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiElement.h"
#include "TextureManager.h"

#include <memory>
#include <string>

enum class ButtonState
{
	DISABLED,
	NORMAL,
	FOCUSED,
	PRESSED,
	SELECTED
};

class GuiButton : public GuiElement
{
public:
	GuiButton() = default;
	~GuiButton() override
	{
		app->tex->Unload(textureID);
	}
	explicit GuiButton(
		uPoint pos,
		uPoint size,
		std::string const &str,
		std::function<int()> const& funcPtr,
		std::vector<SDL_Rect> const& buttonStates
	);

	int Update() override;
	bool Draw() const override;
	void DrawHorizontalSegment(iPoint topLeftPosition, SDL_Rect currentSlice) const;
	void DrawHorizontalBox(iPoint topLeftPosition, SDL_Rect currentSlice) const;

	void MouseEnterHandler() override;
	void MouseLeaveHandler() override;

	void DebugDraw() const;

private:
    std::string text = "";
	int font = 0;
    int textureID;

	int xAdvance = 4;
	SDL_Rect normalRect;
	SDL_Rect pressedRect;
	SDL_Rect focusedRect;
	iPoint textureSegments{ 3,3 };
	iPoint offset;

	ButtonState currentState = ButtonState::DISABLED;
};

#endif __GUIBUTTON_H__