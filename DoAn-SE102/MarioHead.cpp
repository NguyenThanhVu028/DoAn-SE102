#include "MarioHead.h"
#include "QuestionBlock.h"
#include "LevelUpQuestionBlock.h"
#include "Pipe.h"

void CMarioHead::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width * 0.5f;
	top = y - height * 0.5f;
	right = x + width * 0.5f;
	bottom = y + height * 0.5f;
}

void CMarioHead::OnCollisionWith(LPCOLLISIONEVENT e) {
	//if (dynamic_cast<CQuestionBlock*>(e->obj)) {
	//	dynamic_cast<CQuestionBlock*>(e->obj)->OnCollisionWith(e);
	//}
	if (e->obj->IsBlocking() && e->ny > 0) isBlocked = true;
	if (e->ny > 0) {
		LPCOLLISIONEVENT newEvent = new CCollisionEvent(0, 0, 0);
		*newEvent = *e;
		hitBlocks.push_back(newEvent);
	}
	if (dynamic_cast<CPipe*>(e->obj)) {
		enterablePipe = e->obj;
	}
}

void CMarioHead::ClearHitBlocks() {
	for (auto i : hitBlocks) delete i;
	hitBlocks.clear();
}

void CMarioHead::ProcessHitBlocks() {
	//IF Mario's head hit multiple blocks, only send collision event to the closest one

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
			if (x >= bL && x <= bR) {
				hitBlock = i->obj;
				e = i;
			}
		}
	}
	if(hitBlock != NULL)
		hitBlock->OnCollisionWith(e);
}

void CMarioHead::ProcessCollision(DWORD dt) {
	ClearHitBlocks();
	isBlocked = false; enterablePipe = NULL;
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 0, 1, 0, -1);
	ProcessHitBlocks();
}