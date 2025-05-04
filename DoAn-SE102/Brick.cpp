#include "Brick.h"
#include "MarioHead.h"
#include "GameObjectsManager.h"
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
	else if (CGame::GetInstance()->GetTickCount() - pButton_start < PBUTTON_TIME) aniId = COIN_ANIMATION_STILL;
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
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		if (e->ny > 0) {
			bounce_time_start = CGame::GetInstance()->GetTickCount();
		}
	}
}