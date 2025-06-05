#pragma once
#include "MovableGameObject.h"

#define FINAL_REWARD_WIDTH 4
#define FINAL_REWARD_HEIGHT 4

#define FINAL_REWARD_LEVITATE_SPEED 0.1f

#define FINAL_REWARD_CHANGE_ITEM_TIME 100

#define FINAL_REWARD_TOTAL_ITEMS 3
#define FINAL_REWARD_ITEM1_SPRITE 70051
#define FINAL_REWARD_ITEM2_SPRITE 70041
#define FINAL_REWARD_ITEM3_SPRITE 70011

#define FINAL_REWARD_ITEM1_ANIMATION 70051
#define FINAL_REWARD_ITEM2_ANIMATION 70041
#define FINAL_REWARD_ITEM3_ANIMATION 70011

class CFinalReward : public CMovableGameObject
{
private:
	int currentItem;
	bool isCollected;
	ULONGLONG lastChangeItemTime;
public:
	CFinalReward(float x, float y) : CMovableGameObject(x, y) {
		currentItem = 1;
		isCollected = false;
		lastChangeItemTime = CGame::GetInstance()->GetTickCount();
		vx = vy = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt);
	void Render();
	int IsBlocking() { return 0; }
	
	void Collect();
	bool IsCollected() { return isCollected; }
};

