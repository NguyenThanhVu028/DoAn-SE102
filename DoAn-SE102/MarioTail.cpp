#include "MarioTail.h"
#include "GameObjectsManager.h"
#include "debug.h"

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - MARIO_TAIL_WIDTH * 0.5f;
	top = y - MARIO_TAIL_HEIGHT * 0.5f;
	right = x + MARIO_TAIL_WIDTH * 0.5f;
	bottom = y + MARIO_TAIL_HEIGHT * 0.5f;
}

void CMarioTail::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CEnemy*>(e->obj)) {
		if (dynamic_cast<CEnemy*>(e->obj)->IsDead() || !dynamic_cast<CEnemy*>(e->obj)->IsEnabled()) {
			return;
		}
	}
	LPCOLLISIONEVENT newEvent = new CCollisionEvent(0, 0, 0);
	*newEvent = *e;
	hitObjects.push_back(newEvent);
}

void CMarioTail::ClearHitObjects() {
	for (auto i : hitObjects) delete i;
	hitObjects.clear();
}

void CMarioTail::ProcessHitObjects() {
	for (auto i : hitObjects) {
		if (dynamic_cast<CEnemy*>(i->obj)) {
			dynamic_cast<CEnemy*>(i->obj)->OnCollisionWithMarioTail(i);
			//if (!(dynamic_cast<CEnemy*>(i->obj)->IsUntouchable())) {
			//	float oX, oY; i->obj->GetPosition(oX, oY);
			//	CGameObjectsManager::GetInstance()->GetScoreEffect(oX, oY, 100);
			//}
		}
		else i->obj->OnCollisionWith(i);
	}
}

void CMarioTail::ProcessCollision(DWORD dt) {
	if (!isEnabled) return;
	ClearHitObjects();
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0, -1);
	ProcessHitObjects();
}