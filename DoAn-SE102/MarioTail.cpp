#include "MarioTail.h"
#include "GameObjectsManager.h"

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - MARIO_TAIL_WIDTH * 0.5f;
	top = y - MARIO_TAIL_HEIGHT * 0.5f;
	right = x + MARIO_TAIL_WIDTH * 0.5f;
	bottom = y + MARIO_TAIL_HEIGHT * 0.5f;
}

void CMarioTail::OnCollisionWith(LPCOLLISIONEVENT e) {
	LPCOLLISIONEVENT newEvent = new CCollisionEvent(0, 0, 0);
	*newEvent = *e;
	hitBlocks.push_back(newEvent);
}

void CMarioTail::ClearHitBlocks() {
	for (auto i : hitBlocks) delete i;
	hitBlocks.clear();
}

void CMarioTail::ProcessHitBlocks() {
	LPGAMEOBJECT hitBlock = NULL;
	LPCOLLISIONEVENT e = NULL;
	for (auto i : hitBlocks) {
		if (hitBlock == NULL) {
			hitBlock = i->obj;
			e = i;
		}
		else {
			float bL, bT, bR, bB;
			i->obj->GetBoundingBox(bL, bT, bR, bB);
			if (y >= bT && y <= bB) {
				hitBlock = i->obj;
				e = i;
			}
		}
	}
	if (hitBlock != NULL)
		hitBlock->OnCollisionWith(e);
}

void CMarioTail::ProcessCollision(DWORD dt) {
	if (!isEnabled) return;
	ClearHitBlocks();
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0, -1);
	ProcessHitBlocks();
}