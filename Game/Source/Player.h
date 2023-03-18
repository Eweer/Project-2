#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Sprite.h"
#include "Transform.h"
#include "Point.h"

class Player : public Sprite, public Transform
{
public:
	Player();
	~Player();

	void HandleInput();
	void DebugDraw() const;
	void Draw() const;
	void Create();
private:
	void Move();
	void AnimateMove();
	void SmoothMove();
	void CheckMoveInput();

	int moveTimer = 0;
	iPoint moveVector{ 0 };
	int speed = 1;
	const int timeForATile = 2;
	const int tileSize = 16;

	int animTimer = 0;

	SDL_Rect currentSpriteSlice{ 0 };
};

#endif //__PLAYER_H__

