#include "Mushroom.h"
#include "Game.h"
#include "GameObjectsManager.h"
#include "Mario.h"

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - MUSHROOM_WIDTH * 0.5f;
	top = y - MUSHROOM_HEIGHT * 0.5f;
	right = x + MUSHROOM_WIDTH * 0.5f;
	bottom = top + MUSHROOM_HEIGHT;
}

void CMushroom::Render() {
	if (isDeleted) return;
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - MUSHROOM_WIDTH * 0.5f || x > cX + screenWidth + MUSHROOM_WIDTH * 0.5f) return;
	if (y < cY - MUSHROOM_HEIGHT * 0.5f || y > cY + screenHeight + MUSHROOM_HEIGHT * 0.5f) { isDeleted = true; return; }
	CSprites::GetInstance()->Get(MUSHROOM_SPRITE)->Draw(x, y);
}

void CMushroom::Update(DWORD dt) {
	if (IsRising()) {
		vx = 0;
		ay = MUSHROOM_GRAVITY;
		ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
		y = spawnY - MUSHROOM_RISING_HEIGHT * (timer * 1.0f / MUSHROOM_RISING_TIME);
		CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 1, 0, 0, 0);
	}
	else {
		vx = tempVx;
		ay = MUSHROOM_GRAVITY;
		vy += ay * dt;
		CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 1, 0, 1, 0);
	}
}

void CMushroom::OnNoCollision(DWORD dt) {
	if (IsRising()) return;
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMario*>(e->obj)) {
		e->obj->OnCollisionWith(e); return;
	}
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
}

bool CMushroom::IsRising() { return CGame::GetInstance()->GetTickCount() - checkPoint < MUSHROOM_RISING_TIME; }