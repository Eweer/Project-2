#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Point.h"

class Player
{
public:
	Player();
	~Player();

	void HandleInput();
private:
	void Move();

	int textureID = -1;

	iPoint position = {};

};

#endif //__PLAYER_H__
