#include "GreenMushroomBrick.h"
#include "MarioHead.h"
#include "MarioTail.h"

void CGreenMushroomBrick::Update(DWORD dt) {
	if (item != NULL) {
		if (item->IsDeleted()) {
			delete item; item = NULL;
		}
	}
	if (CGame::GetInstance()->GetTickCount() - bounce_time_start > BRICK_BOUNCE_TIME && !hasSummonedItem && !isAvailable) {
		if (item == NULL) {
			item = new CGreenMushroom(x, y, nx);
			item->ReEnable();
			hasSummonedItem = true;
		}
	}
	if (item != NULL) item->Update(dt);
}

void CGreenMushroomBrick::Render() {
	if (item != NULL) item->Render();
	CBrick::Render();
}

void CGreenMushroomBrick::SpecialEffect(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
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