#pragma once
#include "LevelUpItem.h"

#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16

#define MUSHROOM_MOVING_SPEED 0.05f
#define MUSHROOM_EMERGING_SPEED 0.01f
#define MUSHROOM_GRAVITY 0.00075f

#define MUSHROOM_RISING_TIME 500
#define MUSHROOM_RISING_HEIGHT 17
//Sprite Id
#define MUSHROOM_SPRITE 70011

class CMushroom : public CLevelUpItem
{
	ULONGLONG checkPoint;
	float spawnX, spawnY;
public:
	CMushroom(float x, float y, int nx = 1) : CLevelUpItem(x, y) { checkPoint = CGame::GetInstance()->GetTickCount(); spawnX = x; spawnY = y; ay = MUSHROOM_GRAVITY; vx = (nx > 0)? MUSHROOM_MOVING_SPEED : -MUSHROOM_MOVING_SPEED;}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsRising();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

