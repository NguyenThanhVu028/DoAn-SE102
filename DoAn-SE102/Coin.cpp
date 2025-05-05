#include "Coin.h"
#include "Mario.h"
void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - COIN_WIDTH * 0.5f;
	top = y - COIN_HEIGHT * 0.5f;
	right = x + COIN_WIDTH * 0.5f;
	bottom = y + COIN_HEIGHT * 0.5f;
}

void CCoin::Render() {
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - 8 || x > cX + screenWidth + 8 || y < cY - 8 || y > cY + screenHeight + 8) return;

	int aniId;
	if (CGame::GetInstance()->IsPButtonStarted()) aniId = BRICK_ANIMATION_AVAILABLE;
	else aniId = COIN_ANIMATION;

	float tempX = x, tempY = y;
	LONGLONG bounce_timer = CGame::GetInstance()->GetTickCount() - bounce_time_start;
	if (bounce_timer < COIN_BOUNCE_TIME) {
		if (bounce_timer < COIN_BOUNCE_TIME * 0.5f) {
			tempY = y - ((bounce_timer / (COIN_BOUNCE_TIME * 0.5f)) * COIN_BOUNCE_DISTANCE);
		}
		else {
			tempY = y - ((1 - (bounce_timer - COIN_BOUNCE_TIME * 0.5f) / (COIN_BOUNCE_TIME * 0.5f)) * COIN_BOUNCE_DISTANCE);
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(tempX, tempY);
}

void CCoin::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!IsInteractable()) return;
	if (!IsBlocking()) {
		if (dynamic_cast<CMario*>(e->src_obj)) {
			CGame::GetInstance()->IncreaseCoin(1);
			Delete();
		}
	}
	else {
		if (dynamic_cast<CMarioHead*>(e->src_obj)) {
			if (e->ny > 0) {
				bounce_time_start = CGame::GetInstance()->GetTickCount();
				CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
				if (mario->GetLevel() != MarioLevel::SMALL) Delete();
				return;
			}
		}
		if (dynamic_cast<CMarioTail*>(e->src_obj)) {
			bounce_time_start = CGame::GetInstance()->GetTickCount();
			Delete();
		}
	}
}