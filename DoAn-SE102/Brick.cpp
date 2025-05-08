#include "Brick.h"
#include "MarioHead.h"
#include "GameObjectsManager.h"
#include "Mario.h"
void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BRICK_WIDTH * 0.5f;
	top = y - BRICK_HEIGHT * 0.5f;
	right = x + BRICK_WIDTH * 0.5f;
	bottom = y + BRICK_HEIGHT * 0.5f;
}

void CBrick::Render() {
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - 8 || x > cX + screenWidth + 8 || y < cY - 8 || y > cY + screenHeight + 8) return;

	int aniId;
	if (!isAvailable) aniId = BRICK_ANIMATION_UNAVAILABLE;
	else if (CGame::GetInstance()->IsPButtonStarted()) aniId = COIN_ANIMATION_STILL;
	else aniId = BRICK_ANIMATION_AVAILABLE;

	float tempX = x, tempY = y;
	LONGLONG bounce_timer = CGame::GetInstance()->GetTickCount() - bounce_time_start;
	if (bounce_timer < BRICK_BOUNCE_TIME) {
		if (bounce_timer < BRICK_BOUNCE_TIME * 0.5f) {
			tempY = y - ((bounce_timer / (BRICK_BOUNCE_TIME * 0.5f)) * BRICK_BOUNCE_DISTANCE);
		}
		else {
			tempY = y - ((1 - (bounce_timer - BRICK_BOUNCE_TIME * 0.5f) / (BRICK_BOUNCE_TIME * 0.5f)) * BRICK_BOUNCE_DISTANCE);
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(tempX, tempY);
}

void CBrick::OnCollisionWith(LPCOLLISIONEVENT e) {
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
				SpecialEffect(e);
				return;
			}
		}
		if (dynamic_cast<CMarioTail*>(e->src_obj)) {
			bounce_time_start = CGame::GetInstance()->GetTickCount();
			SpecialEffect(e);
			return;
		}
		if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
			SpecialEffect(e);
		}
	}
}

void CBrick::SpecialEffect(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
		if (mario->GetLevel() != MarioLevel::SMALL) {
			CGameObjectsManager::GetInstance()->GetDebrisEffect(x, y);
			Delete();
		}
	}
	if (dynamic_cast<CMarioTail*>(e->src_obj)) {
		CGameObjectsManager::GetInstance()->GetDebrisEffect(x, y);
		Delete();
	}
	if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
		if (dynamic_cast<CKoopaTroopa*>(e->src_obj)->IsMoving() && e->nx != 0) {
			CGameObjectsManager::GetInstance()->GetDebrisEffect(x, y);
			Delete();
		}
	}
}