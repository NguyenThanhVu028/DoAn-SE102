#include "LevelUpQuestionBlock.h"
#include "Goomba.h"

void CLevelUpQuestionBlock::SpecialEffect(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		float pX, pY;
		dynamic_cast<CMarioHead*>(e->src_obj)->GetPosition(pX, pY);
		if (pX < x) nx = 1;
		else nx = -1;
		isAvailable = false;
	}
	if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
		float pX, pY;
		e->src_obj->GetPosition(pX, pY);
		if (pX < x) nx = 1;
		else nx = -1;
		isAvailable = false;
	}
	if (dynamic_cast<CMarioTail*>(e->src_obj)) {
		float pX, pY;
		e->src_obj->GetPosition(pX, pY);
		if (pX < x) nx = 1;
		else nx = -1;
		isAvailable = false;
	}
}

void CLevelUpQuestionBlock::Render() {
	if (dynamic_cast<CMushroom*>(item)) item->Render();	
	CQuestionBlock::Render();
	if (dynamic_cast<CLeaf*>(item)) item->Render();
}

void CLevelUpQuestionBlock::Update(DWORD dt) {
	if (item != NULL) {
		if (item->IsDeleted()) {
			delete item; item = NULL;
		}
	}
	if (CGame::GetInstance()->GetTickCount() - bounce_time_start > QUESTIONBLOCK_BOUNCE_TIME && !hasSummonedItem && !isAvailable) {
		if (item == NULL) { 
			if (dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer())->GetLevel() == MarioLevel::SMALL) item = new CMushroom(x, y, nx);
			else item = new CLeaf(x, y); 
			item->ReEnable(); 
			hasSummonedItem = true; }
	}
	if (item != NULL) item->Update(dt);
}