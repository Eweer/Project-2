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
	texture = app->tex->Load("Assets/UI/Portrait_frame.png");
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
	
	app->render->DrawTexture(texture.get(), GetPosition().x, GetPosition().y);
	app->fonts->Draw(text, iPoint(GetPosition().x, GetPosition().y), font);

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
