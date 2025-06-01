#pragma once
#include "Game.h"
#include "GameObject.h"
#include "GameObjectsManager.h"
#include "Mario.h"

#define MIN_ENTER_TIME 100
#define ENTER_SPEED 0.025f

class CMarioEnterPipeDecoy : public CGameObject
{
	bool isOverlapPipe;
	float enterVelocity;
	ULONGLONG enter_start;
public:
	CMarioEnterPipeDecoy(float x, float y, bool direction) : CGameObject(x, y) {
		isOverlapPipe = false;
		CMario* player = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
		if (player != NULL) {
			player->Hide();
		}
		enterVelocity = (direction == 0)? - ENTER_SPEED : ENTER_SPEED;
		enter_start = CGame::GetInstance()->GetTickCount();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
};

