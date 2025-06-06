#pragma once
#include "LevelUpItem.h"

#define LEAF_WIDTH 16
#define LEAF_HEIGHT 16

#define LEAF_RISE_TIME 400
#define LEAF_HALF_CYCLE_TIME 500

#define LEAF_ACCEL_X 0.00006f
#define LEAF_ACCEL_Y -0.00025f

#define LEAF_VX 0.06f
#define LEAF_VY 0.09f
#define LEAF_INITIAL_VY -0.22f
#define LEAF_INITIAL_AY 0.0005f

//Sprite Id
#define LEAF_SPRITE_LEFT 70021
#define LEAF_SPRITE_RIGHT 70022

class CLeaf : public CLevelUpItem
{
	ULONGLONG checkPoint;
	bool rised;
public:
	CLeaf(float x, float y) : CLevelUpItem(x, y) { 
		nx = -1;
		vx = 0;
		vy = LEAF_INITIAL_VY;
		checkPoint = CGame::GetInstance()->GetTickCount();
		ax = 0;
		ay = LEAF_INITIAL_AY;
		rised = false;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

