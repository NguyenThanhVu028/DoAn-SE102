#include "FinalReward.h"

void CFinalReward::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - FINAL_REWARD_WIDTH * 0.5f;
	top = y - FINAL_REWARD_HEIGHT * 0.5f;
	right = x + FINAL_REWARD_WIDTH * 0.5f;
	bottom = y + FINAL_REWARD_HEIGHT * 0.5f;
}

void CFinalReward::Update(DWORD dt) {
	if ((CGame::GetInstance()->GetTickCount() - lastChangeItemTime) > FINAL_REWARD_CHANGE_ITEM_TIME && !isCollected) {
		lastChangeItemTime = CGame::GetInstance()->GetTickCount();
		currentItem++; if (currentItem > FINAL_REWARD_TOTAL_ITEMS) currentItem = 1;
	}
	if (isCollected) {
		y += vy * dt;
	}
}

void CFinalReward::Render() {
	switch (currentItem) {
	case 1:
		if (!isCollected) CSprites::GetInstance()->Get(FINAL_REWARD_ITEM1_SPRITE)->Draw(x, y);
		else CAnimations::GetInstance()->Get(FINAL_REWARD_ITEM1_ANIMATION)->Render(x, y);
		break;
	case 2:
		if (!isCollected) CSprites::GetInstance()->Get(FINAL_REWARD_ITEM2_SPRITE)->Draw(x, y);
		else CAnimations::GetInstance()->Get(FINAL_REWARD_ITEM2_ANIMATION)->Render(x, y);
		break;
	case 3:
		if (!isCollected) CSprites::GetInstance()->Get(FINAL_REWARD_ITEM3_SPRITE)->Draw(x, y);
		else CAnimations::GetInstance()->Get(FINAL_REWARD_ITEM3_ANIMATION)->Render(x, y);
		break;
	default:
		if (!isCollected) CSprites::GetInstance()->Get(FINAL_REWARD_ITEM1_SPRITE)->Draw(x, y);
		else CAnimations::GetInstance()->Get(FINAL_REWARD_ITEM1_ANIMATION)->Render(x, y);
		break;
	}
}

void CFinalReward::Collect() {
	isCollected = true;
	vy = -FINAL_REWARD_LEVITATE_SPEED;
}
