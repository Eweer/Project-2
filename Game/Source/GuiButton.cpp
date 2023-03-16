#include "GuiButton.h"
#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Fonts.h"

GuiButton::GuiButton(uPoint pos, uPoint size, std::string const &str, std::function<void()> const& funcPtr) :
	text(str),
	currentState(ButtonState::NORMAL)
{
	Initialize(funcPtr, pos, size);
	texture = app->tex->Load("Assets/UI/GUI_4x_sliced.png");
}

void GuiButton::Update()
{
	if (currentState == ButtonState::DISABLED)
		return;

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		currentState = ButtonState::PRESSED;

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
		ExecuteFunction();
}

bool GuiButton::Draw()
{
	if (!texture) return false;
	
	SDL_Rect currentSlice(rect);

	currentSlice.x += xAdvance;
	currentSlice.y += xAdvance;

	iPoint currentPos(GetPosition().x, GetPosition().y);
	iPoint buttonSize(GetSize().x, GetSize().y);

	auto yRepeats = (buttonSize.y % currentSlice.h);

	for (int j = 0; j < yRepeats; j++)
	{

		app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);

		auto xRepeats = (buttonSize.x % currentSlice.w) - 2;

		currentPos.x += currentSlice.w;
		currentSlice.x += currentSlice.w + xAdvance;


		for (int i = 0; i < xRepeats; i++)
		{
			app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);
			currentPos.x += currentSlice.w;
		}

		currentSlice.x += currentSlice.w + xAdvance;

		app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);

		currentPos.x = GetPosition().x;
		currentSlice.x = rect.x + xAdvance;
		currentPos.y += currentSlice.h;
		if (j == yRepeats - 2 || j == 0)
		{
			currentSlice.y += currentSlice.h + xAdvance;
		}
	}

	//app->fonts->Draw(text, iPoint(GetPosition().x, GetPosition().y), font);

	return true;
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
