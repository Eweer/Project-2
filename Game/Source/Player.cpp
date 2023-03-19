#include "App.h"
#include "Player.h"

#include "Map.h"

#include "Input.h"
#include "Render.h"

Player::Player() = default;

Player::~Player() = default;

void Player::HandleInput()
{
	Move();
}

void Player::DebugDraw() const
{
	SDL_Rect debugPosition = { position.x, position.y, size.x, size.y };
	app->render->DrawShape(debugPosition, false, SDL_Color(255, 0, 0, 255));
}

void Player::Draw() const
{
	DebugDraw();
	app->render->DrawTexture(DrawParameters(GetTextureID(), position).Section(&currentSpriteSlice));
}

void Player::Create()
{
	Sprite::Initialize("Assets/Maps/Slime.png", 4);
	position = { 48, 272 };
	size = { 48, 48 };
	currentSpriteSlice = {
		(GetTextureIndex().x + 1) * size.x,
		GetTextureIndex().y * size.y,
		size.x,
		size.y
	};
}

void Player::Move()
{
	if (!moveVector.IsZero())
	{
		AnimateMove();
		SmoothMove();
	}
	else
	{
		CheckMoveInput();
	}
}

void Player::AnimateMove()
{
	if (animTimer == 8)
	{
		currentSpriteSlice.x += size.x;
		if (currentSpriteSlice.x == size.x * (GetTextureIndex().x + 3))
		{
			currentSpriteSlice.x = GetTextureIndex().x * size.x;
		}
		animTimer = 0;
	}
	else
	{
		animTimer++;
	}
}

void Player::SmoothMove()
{
	if (moveTimer == timeForATile)
	{
		moveTimer = 0;
		position += (moveVector * speed);
		if (position.x % tileSize == 0 && position.y % tileSize == 0)
		{
			moveVector.SetToZero();
		}
	}
	else
	{
		moveTimer++;
	}
}

void Player::CheckMoveInput()
{
	using enum KeyState;
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		moveVector.y = -1;
		currentSpriteSlice.y = (GetTextureIndex().y + 3) * size.y;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		moveVector.x = -1;
		currentSpriteSlice.y = (GetTextureIndex().y + 1) * size.y;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		moveVector.y = 1;
		currentSpriteSlice.y = GetTextureIndex().y * size.y;
	}
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		moveVector.x = 1;
		currentSpriteSlice.y = (GetTextureIndex().y + 2) * size.y;
	}
}

