#pragma once
#include "GameObject.h"
#include "Mario.h"

#define QUESTIONBLOCK_BOUNCE_TIME 150
#define QUESTIONBLOCK_BOUNCE_DISTANCE 16.0f

#define QUESTIONBLOCK_HEIGHT 16
#define QUESTIONBLOCK_WIDTH 12

//Aniamtion Ids
#define QUESTIONBLOCK_ANIMATION_AVAILABLE 20011
#define QUESTIONBLOCK_ANIMATION_UNAVAILABLE 20012

class CQuestionBlock : public CGameObject
{
protected:
	LONGLONG bounce_time_start;
	bool isAvailable;
	bool isVisible;
public:
	CQuestionBlock(float x, float y, bool isVisible = true) : CGameObject(x + 8, y + 8) {
		bounce_time_start = CGame::GetInstance()->GetTickCount() - QUESTIONBLOCK_BOUNCE_TIME - 10;
		isAvailable = true;
		this->isVisible = isVisible;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; };
	bool IsInteractable() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start > QUESTIONBLOCK_BOUNCE_TIME) && isAvailable; }
	bool IsBouncing() { return (CGame::GetInstance()->GetTickCount() - bounce_time_start < QUESTIONBLOCK_BOUNCE_TIME); }
};

