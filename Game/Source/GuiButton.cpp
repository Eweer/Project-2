#include "GuiButton.h"
#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Fonts.h"

#include "Log.h"

GuiButton::GuiButton(uPoint pos, uPoint size, std::string const &str, std::function<int()> const& funcPtr, std::vector<SDL_Rect> const &buttonStates) :
	text(str),
	currentState(ButtonState::NORMAL)
{
	Initialize(funcPtr, pos, size);
	textureID = app->tex->Load("Assets/UI/GUI_4x_sliced.png");
	switch (buttonStates.size())
	{
	case 3:
		focusedRect = buttonStates[2];
	case 2:
		pressedRect = buttonStates[1];
	case 1:
		normalRect = buttonStates[0];
		break;
	default:
		LOG("Invalid button states size");
	}
}

int GuiButton::Update()
{
	using enum ButtonState;
	if (currentState == DISABLED)
		return 0;

	if (IsMouseHovering())
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		{
			currentState = PRESSED;
		}
		else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
		{
			return ExecuteFunction();
			currentState = NORMAL;
		}
		else
		{
			currentState = FOCUSED;
		}
	}
	else
	{
		currentState = NORMAL;
	}
	return 0;
}

bool GuiButton::Draw() const
{
	if (textureID == -1) return false;

	SDL_Rect currentSlice;

	switch (currentState)
	{
		using enum ButtonState;
		case NORMAL:
		case DISABLED:
			currentSlice = normalRect;
			break;
		case FOCUSED:
		case SELECTED:
			currentSlice = focusedRect;
			break;
		case PRESSED:
			currentSlice = pressedRect;
			break;
	}

	currentSlice.x += xAdvance;
	currentSlice.y += xAdvance;

	iPoint currentPos(GetPosition().x, GetPosition().y);

	auto yRepeats = (static_cast<int>(GetSize().y) / currentSlice.h);

	int firstSideY = currentSlice.y;

	for (int j = 0; j < yRepeats; j++)
	{
		
		if (textureSegments.x == 2)
		{
			DrawHorizontalBox(currentPos, currentSlice);
		}
		else
		{
			DrawHorizontalSegment(currentPos, currentSlice);
		}

		// Go to next draw line
		currentPos.y += currentSlice.h;

		switch (textureSegments.y)
		{
			case 1:
			{
				continue;
			}	
			case 2:
			{
				if (j == 0) currentSlice.y += currentSlice.h + xAdvance;
				else break;
			}
			default:
			{
				// In first iteration we keep the Y coordinate of first side
				if (j == 0)
				{
					currentSlice.y += currentSlice.h + xAdvance;
					firstSideY = currentSlice.y;
				}
				// In last iteration we go to the down corner
				else if (j == yRepeats - 2)
				{
					currentSlice.y = firstSideY + (textureSegments.y - 2) * (currentSlice.h + xAdvance);
				}
				// In any other iteration, we iterate over the number of sides segments (different textures) there are
				else
				{
					if (j % (textureSegments.y - 2) != 0) currentSlice.y += currentSlice.h + xAdvance;
					else currentSlice.y = firstSideY;
				}
			}
		}
	}

	auto centerPoint = iPoint(GetPosition().x, GetPosition().y);
	centerPoint += iPoint(GetSize().x/2, GetSize().y/2);

	app->fonts->DrawMiddlePoint(text, centerPoint, font);

	return true;
}

void GuiButton::DrawHorizontalSegment(iPoint topLeftPosition, SDL_Rect currentSlice) const
{
	// Draw left corner texture
	app->render->DrawTexture(DrawParameters(textureID, topLeftPosition).Section(&currentSlice));

	// Go to next draw position
	topLeftPosition.x += currentSlice.w;

	// Get number of side fragments (minus corners) needed to fill the side
	auto xRepeats = (static_cast<int>(GetSize().x) / currentSlice.w) - 2;

	// If there are side segments set texture to first side fragment
	if (textureSegments.x > 2)
	{
		currentSlice.x += currentSlice.w + xAdvance;
	}

	auto firstSideX = currentSlice.x;

	// Draw sides
	for (int i = 0; i < xRepeats; i++)
	{
		app->render->DrawTexture(DrawParameters(textureID, topLeftPosition).Section(&currentSlice));

		topLeftPosition.x += currentSlice.w;

		// If there are side segments
		if (textureSegments.x > 2)
		{
			// Go to next side fragment, if there are no more, go to previous
			currentSlice.x = (i % (textureSegments.x - 2))
				? currentSlice.x + currentSlice.w + xAdvance
				: firstSideX;
		}
	}

	if (textureSegments.x > 2)
	{
		currentSlice.x = firstSideX + (textureSegments.x - 2) * (currentSlice.w + xAdvance);
	}

	// Draw right corner
	app->render->DrawTexture(DrawParameters(textureID, topLeftPosition).Section(&currentSlice));
}

void GuiButton::DrawHorizontalBox(iPoint topLeftPosition, SDL_Rect currentSlice) const
{
	// Draw left corner
	app->render->DrawTexture(DrawParameters(textureID, topLeftPosition).Section(&currentSlice));

	// Go to next draw position
	topLeftPosition.x += currentSlice.w;

	// Get right corner texture
	currentSlice.x += currentSlice.w + xAdvance;

	// Draw right corner
	app->render->DrawTexture(DrawParameters(textureID, topLeftPosition).Section(&currentSlice));
}

void GuiButton::MouseEnterHandler()
{
	if (currentState != ButtonState::DISABLED)
		currentState = ButtonState::FOCUSED;
}

void GuiButton::MouseLeaveHandler()
{
	if (currentState != ButtonState::DISABLED)
		currentState = ButtonState::NORMAL;
}

void GuiButton::DebugDraw() const
{
	SDL_Rect debugRect(GetPosition().x, GetPosition().y, GetSize().x, GetSize().y);

	app->render->DrawRectangle(debugRect, SDL_Color(255, 0, 0, 255), false);
}
