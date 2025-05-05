#pragma once
#include "GameObject.h"
#define COIN_BOUNCE_TIME 150
#define COIN_BOUNCE_DISTANCE 16.0f

#define COIN_HEIGHT 16
#define COIN_WIDTH 16

//Aniamtion Ids
#define BRICK_ANIMATION_AVAILABLE 20121

#define COIN_ANIMATION 20131

class CCoin : public CGameObject
{
	LONGLONG bounce_time_start;
public:
	CCoin(float x, float y) : CGameObject(x + 8, y + 8) {
		bounce_time_start = CGame::GetInstance()->GetTickCount() - COIN_BOUNCE_TIME - 10;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return CGame::GetInstance()->IsPButtonStarted(); }
	bool IsInteractable() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start > COIN_BOUNCE_TIME); }
	bool IsBouncing() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start < COIN_BOUNCE_TIME); }
	bool AllowOverlap() { return false; }
};

