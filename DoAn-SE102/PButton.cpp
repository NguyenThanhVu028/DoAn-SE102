#include "PButton.h"

void CPButton::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PBUTTON_WIDTH * 0.5f;
	top = y - PBUTTON_HEIGHT * 0.5f;
	right = x + PBUTTON_WIDTH * 0.5f;
	bottom = y + PBUTTON_HEIGHT * 0.5f;
}

void CPButton::Render() {
	int aniId;
	if (isActivated) aniId = PBUTTON_ANIMATION_UNAVAILABLE;
	else aniId = PBUTTON_ANIMATION_AVAILABLE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CPButton::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (isActivated) return;
	if (dynamic_cast<CMario*>(e->src_obj) && e->ny < 0) {
		CGame::GetInstance()->StartPButton();
		isActivated = true;
	}
}