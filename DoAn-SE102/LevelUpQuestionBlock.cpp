#include "LevelUpQuestionBlock.h"

void CLevelUpQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!IsInteractable()) return;
	if (dynamic_cast<CMario*>(e->src_obj)) {
		if (e->ny > 0) {
			float pX, pY;
			dynamic_cast<CMario*>(e->src_obj)->GetPosition(pX, pY);
			if (pX < x) nx = 1;
			else nx = -1;
			bounce_time_start = GetTickCount64();
			isAvailable = false;
		}
	}
}

void CLevelUpQuestionBlock::Render() {
	if (item != NULL) item->Render();
	CQuestionBlock::Render();
	
}

void CLevelUpQuestionBlock::Update(DWORD dt) {
	if (item != NULL) {
		if (item->IsDeleted()) {
			delete item; item = NULL;
		}
	}
	if (GetTickCount64() - bounce_time_start > QUESTIONBLOCK_BOUNCE_TIME && !hasSummonedItem && !isAvailable) {
		if (item == NULL) { item = new CMushroom(x, y, nx); item->ReEnable(); hasSummonedItem = true; }
	}
	if (item != NULL) item->Update(dt);
}