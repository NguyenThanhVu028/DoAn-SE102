#pragma once
#include "Effect.h"
#define DEBRIS_DEFAULT_DURATION 300
#define DEBRIS_VX 0.07f
#define DEBRIS_START_VY_LV0 -0.25f
#define DEBRIS_START_VY_LV1 -0.33f
#define DEBRIS_GRAVITY 0.018f

#define DEBRIS_WIDTH 8
#define DEBRIS_HEIGHT 8

//Ani Ids
#define DEBRIS_EFFECT_ANIMATION 30031

class CDebrisEffect : public CEffect
{
	int direction;
	int level;
	float vx, vy;
public:
	CDebrisEffect(float x, float y, int direction, int level, ULONGLONG duration = DEBRIS_DEFAULT_DURATION) : CEffect(x, y, duration){
		this->direction = direction;
		this->level = level;
		vx = (direction == 1) ? DEBRIS_VX : -DEBRIS_VX;
		vy = (level == 0) ? DEBRIS_START_VY_LV0 : DEBRIS_START_VY_LV1;
	}
	void Update(DWORD dt);
	void Render();
	void ReEnable();
	void SetDirection(int nx) { direction = nx; }
	void SetLevel(int lv) { level = lv; }
};

