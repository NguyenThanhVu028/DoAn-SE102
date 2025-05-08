#pragma once
#include "Goomba.h"

#define RED_GOOMBA_CYCLE 2000
#define RED_GOOMBA_SHORT_JUMP_SPEED -0.1f
#define RED_GOOMBA_LONG_JUMP_SPEED -0.2f

#define RED_GOOMBA_ANIMATION_WALK 80131
#define RED_GOOMBA_ANIMATION_FLATENNED 80141
#define RED_GOOMBA_ANIMATION_UPSIDE_DOWN 80151
#define RED_GOOMBA_WINGS_ANIMATION_FLAPPING 80161
#define RED_GOOMBA_WINGS_ANIMATION_CLOSED 80162

#define RED_GOOMBA_UNTOUCHABLE_TIME 50

class CRedGoomba : public CGoomba
{
	bool hasWings;
	bool isCharging;
	ULONGLONG jump_timer;
public:
	CRedGoomba(float x, float y, int nx = 1) : CGoomba(x, y, nx) {
		hasWings = true;
		isCharging = false;
		jump_timer = 0;
		untouchable_start = CGame::GetInstance()->GetTickCount();
	}

	void Render();
	void Update(DWORD dt);
	void SetEnable(bool t);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	bool IsUntouchable();
};

