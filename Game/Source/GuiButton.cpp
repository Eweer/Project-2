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
	


	iPoint texturePos(rect.x, rect.y);
	texturePos.x += xAdvance;
	texturePos.y += xAdvance;

	iPoint textureSize(rect.w, rect.h);

	iPoint currentPos(GetPosition().x, GetPosition().y);
	iPoint buttonSize(GetSize().x, GetSize().y);

	auto yRepeats = (buttonSize.y % textureSize.y);

	for (int j = 0; j < yRepeats; j++)
	{
		SDL_Rect currentSlice{ texturePos.x, texturePos.y, textureSize.x, textureSize.y };

		app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);

		auto xRepeats = (buttonSize.x % textureSize.x) - 2;

		currentPos.x += textureSize.x;
		texturePos.x += textureSize.x + xAdvance;

		currentSlice = SDL_Rect(texturePos.x, texturePos.y, textureSize.x, textureSize.y);

		for (int i = 0; i < xRepeats; i++)
		{
			app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);
			currentPos.x += textureSize.x;
		}

		texturePos.x += textureSize.x + xAdvance;
		currentSlice = SDL_Rect(texturePos.x, texturePos.y, textureSize.x, textureSize.y);

		app->render->DrawTexture(texture.get(), currentPos.x, currentPos.y, &currentSlice);

		currentPos.x = GetPosition().x;
		texturePos.x = rect.x + xAdvance;
		currentPos.y += textureSize.y;
		if (j == yRepeats - 2 || j == 0)
		{
			texturePos.y += textureSize.y + xAdvance;
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
