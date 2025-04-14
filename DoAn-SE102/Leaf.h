#pragma once
#include "LevelUpItem.h"

#define LEAF_WIDTH 16
#define LEAF_HEIGHT 16

#define LEAF_HALF_CYCLE_TIME 600

#define LEAF_ACCEL_X 0.00004f
#define LEAF_ACCEL_Y -0.0001f

#define LEAF_VX 0.06f
#define LEAF_VY 0.06f
#define LEAF_INITIAL_VY -0.08f

//Sprite Id
#define LEAF_SPRITE_LEFT 70021
#define LEAF_SPRITE_RIGHT 70022

class CLeaf : public CLevelUpItem
{
	ULONGLONG checkPoint;
public:
	CLeaf(float x, float y) : CLevelUpItem(x, y) { 
		nx = -1;
		vx = 0;
		vy = LEAF_INITIAL_VY;
		checkPoint = GetTickCount64(); 
		ax = 0;
		ay = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

