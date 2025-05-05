#pragma once
#include "GameObject.h"
#define BRICK_BOUNCE_TIME 150
#define BRICK_BOUNCE_DISTANCE 16.0f

#define BRICK_HEIGHT 16
#define BRICK_WIDTH 16

//Aniamtion Ids
#define BRICK_ANIMATION_AVAILABLE 20121
#define BRICK_ANIMATION_UNAVAILABLE 20012

#define COIN_ANIMATION_STILL 20132

class CBrick : public CGameObject
{
protected:
	LONGLONG bounce_time_start;
	bool isAvailable;
public:
	CBrick(float x, float y) : CGameObject(x + 8, y + 8) {
		bounce_time_start = CGame::GetInstance()->GetTickCount() - BRICK_BOUNCE_TIME - 10;
		isAvailable = true;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return (!CGame::GetInstance()->IsPButtonStarted() || !isAvailable); }
	//int IsCollidable() { return 1; };
	bool IsInteractable() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start > BRICK_BOUNCE_TIME) && isAvailable; }
	bool IsBouncing() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start < BRICK_BOUNCE_TIME); }
	bool AllowOverlap() { return false; }
	virtual void SpecialEffect(LPCOLLISIONEVENT e);
};

