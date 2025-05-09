#include "PButtonBrick.h"

void CPButtonBrick::SpecialEffect(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		CPButton* newButton = new CPButton(x, y - BRICK_HEIGHT * 0.5f - PBUTTON_HEIGHT * 0.5f);
		CGameObjectsManager::GetInstance()->AddStaticObject(newButton);
		isAvailable = false;
	}
	if (dynamic_cast<CMarioTail*>(e->src_obj)) {
		CPButton* newButton = new CPButton(x, y - BRICK_HEIGHT * 0.5f - PBUTTON_HEIGHT * 0.5f);
		CGameObjectsManager::GetInstance()->AddStaticObject(newButton);
		isAvailable = false;
	}
	if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
		if (dynamic_cast<CKoopaTroopa*>(e->src_obj)->IsMoving() && e->nx != 0) {
			CPButton* newButton = new CPButton(x, y - BRICK_HEIGHT * 0.5f - PBUTTON_HEIGHT * 0.5f);
			CGameObjectsManager::GetInstance()->AddStaticObject(newButton);
			isAvailable = false;
		}
	}
}