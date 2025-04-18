#include "Leaf.h"
#include "GameObjectsManager.h"
#include "Mario.h"

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - LEAF_WIDTH * 0.5f;
	top = y - LEAF_HEIGHT * 0.5f;
	right = x + LEAF_WIDTH * 0.5f;
	bottom = y + LEAF_HEIGHT * 0.5f;
}

void CLeaf::Render() {
	int aniToRender = (nx == 1) ? LEAF_SPRITE_RIGHT : LEAF_SPRITE_LEFT;
	CSprites::GetInstance()->Get(aniToRender)->Draw(x, y);
}

void CLeaf::Update(DWORD dt) {
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 1, 0, 0);
	ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
	if (timer > LEAF_HALF_CYCLE_TIME) {
		nx = -nx;
		ax = -ax;
		checkPoint = CGame::GetInstance()->GetTickCount();
		vx = nx * LEAF_VX;
		vy = LEAF_VY;
		ay = LEAF_ACCEL_Y;
	}
	vx += ax * dt;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;
	//DebugOutTitle(L"x vx %f %f", x, vx);
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMario*>(e->obj)) {
		e->obj->OnCollisionWith(e); return;
	}
}