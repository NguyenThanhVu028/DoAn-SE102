#pragma once
#include "Pipe.h"
#include "GameObjectsManager.h"
#include "Mario.h"
#include "MarioEnterPipeDecoy.h"
#include "UIManager.h"

#define ENTER_ZONE 12
#define ENTER_TIME 1000
#define TRANSITION_TIME 500

class CEnterablePipe : public CPipe
{
protected:
	CMarioEnterPipeDecoy* decoy = NULL;
	bool enterSide;
	bool type;
	int world_id;
	ULONGLONG enter_start;
	ULONGLONG transition_start;
	bool entered;
	bool enter_ended;
public:
	CEnterablePipe(float x, float y, float cellWidth, float cellHeight, int length, bool isVertical, int side, bool enterSide, bool type, int world_id, bool isEnabled = false) : CPipe(x, y, cellWidth, cellHeight, length, isVertical, side) {
		this->enterSide = enterSide;
		this->type = type;
		this->world_id = world_id;
		entered = false; enter_ended = false;
		enter_start = CGame::GetInstance()->GetTickCount() - ENTER_TIME - 10;
		if (isEnabled) {
			CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
			if (decoy == NULL && mario != NULL) {
				float spawnY = y + length * 0.5f * cellHeight + ((enterSide == 0) ? (-length * 0.5f * cellHeight + ((mario->GetLevel() == MarioLevel::SMALL)?MARIO_SMALL_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT)) : (length * 0.5f * cellHeight - ((mario->GetLevel() == MarioLevel::SMALL) ? MARIO_SMALL_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT)));
				mario->SetPosition(x + cellWidth * width * 0.5f, spawnY);
				CGame::GetInstance()->SetCamPos(x + cellWidth * width * 0.5f - CGame::GetInstance()->GetBackBufferWidth() * 0.5f, spawnY);
				bool direction;
				if (enterSide && type) direction = 0;
				else if (enterSide) direction = 1;
				else if (type) direction = 1;
				else direction = 0;
				decoy = new CMarioEnterPipeDecoy(x + cellWidth * width * 0.5f, spawnY, direction);
				if (type == 0) CUIManager::GetInstance()->StartBrightening();
			}
		}
	}
	void Update(DWORD dt);
	virtual void Render();
	virtual void LoadSpriteId() {}
	void RequestEnter(bool direction);
};

