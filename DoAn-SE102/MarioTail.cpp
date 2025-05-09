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
	//LPGAMEOBJECT hitObject = NULL;
	//LPCOLLISIONEVENT e = NULL;
	for (auto i : hitObjects) {
		//if (hitObject == NULL) {
		//	hitObject = i->obj;
		//	e = i;
		//}
		//else {
		//	float bL, bT, bR, bB;
		//	i->obj->GetBoundingBox(bL, bT, bR, bB);
		//	if (y >= bT && y <= bB) {
		//		hitObject = i->obj;
		//		e = i;
		//	}
		//}
		if (dynamic_cast<CEnemy*>(i->obj)) {
			DebugOutTitle(L"Tail %d", CGame::GetInstance()->GetTickCount());
			dynamic_cast<CEnemy*>(i->obj)->OnCollisionWithMarioTail(i);
		}
		else i->obj->OnCollisionWith(i);
	}
	//if (hitObject != NULL) {

	//}
		
}

void CMarioTail::ProcessCollision(DWORD dt) {
	if (!isEnabled) return;
	ClearHitObjects();
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0, -1);
	ProcessHitObjects();
}