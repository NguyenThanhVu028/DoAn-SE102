#include "DebrisEffect.h"
#include "Animations.h"

void CDebrisEffect::Update(DWORD dt) {
	if (!isEnabled) return;
	vy += DEBRIS_GRAVITY;
	x += vx * dt;
	y += vy * dt;

	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - DEBRIS_WIDTH * 0.5f || x > cX + screenWidth + DEBRIS_WIDTH * 0.5f) {
		isEnabled = false;
		return;
	}
	if (y < cY - DEBRIS_HEIGHT * 0.5f || y > cY + screenHeight + DEBRIS_HEIGHT * 0.5f) {
		isEnabled = false;
		return;
	}
}
void CDebrisEffect::Render() {
	if (!isEnabled) return;
	if (CGame::GetInstance()->IsFrozen()) ani->Render1Frame(x, y);
	else ani->Render(x, y);
}
void CDebrisEffect::ReEnable() {
	vx = (direction == 1) ? DEBRIS_VX : -DEBRIS_VX;
	vy = (level == 0) ? DEBRIS_START_VY_LV0 : DEBRIS_START_VY_LV1;
	CEffect::ReEnable();
}