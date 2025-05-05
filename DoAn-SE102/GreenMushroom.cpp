#include "GreenMushroom.h"
#include "Brick.h"
#include "Mario.h"

void CGreenMushroom::Render() {
	if (isDeleted) return;
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - MUSHROOM_WIDTH * 0.5f || x > cX + screenWidth + MUSHROOM_WIDTH * 0.5f) return;
	if (y < cY - MUSHROOM_HEIGHT * 0.5f || y > cY + screenHeight + MUSHROOM_HEIGHT * 0.5f) { isDeleted = true; return; }
	CSprites::GetInstance()->Get(GREEN_MUSHROOM_SPRITE)->Draw(x, y);
}

void CGreenMushroom::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->isOverlap && dynamic_cast<CBrick*>(e->obj)) isOverlapped = true;
	if (dynamic_cast<CMario*>(e->obj)) {
		CGameObjectsManager::GetInstance()->GetScoreEffect(x, y + MUSHROOM_HEIGHT, -1);
		Delete(); return;
	}
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
}