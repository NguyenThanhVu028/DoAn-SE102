#include "Mushroom.h"
#include "Game.h"
#include "GameObjectsManager.h"
#include "Mario.h"
#include "LevelUpQuestionBlock.h"
#include "Brick.h"
#include "Coin.h"

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
	isOverlapped = false;
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 1, 0, 1, 0);
	if (!isOverlapped) isRising = false;
	if (isRising) {
		vx = 0;
		ay = 0;
		//ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
		vy = MUSHROOM_RISING_SPEED;
		//y = spawnY - MUSHROOM_RISING_HEIGHT * (timer * 1.0f / MUSHROOM_RISING_TIME);
	}
	else {
		if(vx == 0) vx = tempVx;
		ay = MUSHROOM_GRAVITY;
		vy += ay * dt;
	}
}

void CMushroom::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->isOverlap && dynamic_cast<CLevelUpQuestionBlock*>(e->obj)) isOverlapped = true;
	if (dynamic_cast<CMario*>(e->obj)) {
		e->obj->OnCollisionWith(e); return;
	}
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
	if (dynamic_cast<CBrick*>(e->obj)) {
		if (dynamic_cast<CBrick*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
	if (dynamic_cast<CCoin*>(e->obj)) {
		if (dynamic_cast<CCoin*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
	if (dynamic_cast<CQuestionBlock*>(e->obj)) {
		if (dynamic_cast<CQuestionBlock*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
}

bool CMushroom::IsRising() { return isRising; }