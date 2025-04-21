#pragma once
#include "LevelUpItem.h"
#include "debug.h"

#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16

#define MUSHROOM_MOVING_SPEED 0.05f
#define MUSHROOM_RISING_SPEED -0.02f
#define MUSHROOM_GRAVITY 0.00075f

//#define MUSHROOM_RISING_TIME 500
//#define MUSHROOM_RISING_HEIGHT 17
//Sprite Id
#define MUSHROOM_SPRITE 70011

class CMushroom : public CLevelUpItem
{
	bool isOverlapped;
	bool isRising;
	float tempVx;
	//ULONGLONG checkPoint;
	//float spawnX, spawnY;
public:
	CMushroom(float x, float y, int nx = 1) : CLevelUpItem(x, y) {
		//checkPoint = CGame::GetInstance()->GetTickCount();
		//this->x = x; this->y = y;
		vx = 0;
		ay = MUSHROOM_GRAVITY; tempVx = (nx > 0) ? MUSHROOM_MOVING_SPEED : -MUSHROOM_MOVING_SPEED;
		isOverlapped = false;
		isRising = true;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsRising();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

