#include "FirePiranhaPlant.h"
#include <algorithm>
void CFirePiranhaPlant::Render() {
	int aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_TL_IDLE;
	switch (direction) {
	case FIRE_PIRANHA_PLANT_TL:
		switch (type) {
		case FIRE_PIRANHA_PLANT_GREEN:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_TL_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_TL_IDLE;
			break;
		case FIRE_PIRANHA_PLANT_RED:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_TL_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_TL_IDLE;
			break;
		}
		break;
	case FIRE_PIRANHA_PLANT_BL:
		switch (type) {
		case FIRE_PIRANHA_PLANT_GREEN:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_BL_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_BL_IDLE;
			break;
		case FIRE_PIRANHA_PLANT_RED:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_BL_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_BL_IDLE;
			break;
		}
		break;
	case FIRE_PIRANHA_PLANT_TR:
		switch (type) {
		case FIRE_PIRANHA_PLANT_GREEN:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_TR_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_TR_IDLE;
			break;
		case FIRE_PIRANHA_PLANT_RED:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_TR_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_TR_IDLE;
			break;
		}
		break;
	case FIRE_PIRANHA_PLANT_BR:
		switch (type) {
		case FIRE_PIRANHA_PLANT_GREEN:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_BR_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_GREEN_ANIMATION_BR_IDLE;
			break;
		case FIRE_PIRANHA_PLANT_RED:
			if (IsRising()) aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_BR_RISING;
			else aniToRender = FIRE_PIRANHA_PLANT_RED_ANIMATION_BR_IDLE;
			break;
		}
		break;
	}
	//DebugOutTitle(L"Direction: %d %d %d", type, IsRising(), aniToRender);
	if (CGame::GetInstance()->IsFrozen())
		CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(x, y);
	else CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
}

void CFirePiranhaPlant::Update(DWORD dt) {
	float pX, pY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
	CPiranhaPlant::Update(dt);
	if (!hasRised) hasShot = false;
	else {
		ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
		if (timer > risingTime + waitingTime * 0.5f) {
			if (!hasShot) {
				float tempAngle = (180 / 3.14f) * atanf(abs((pY - y) / (pX - x)));
				if (pX - x < 0 && pY - y > 0) tempAngle = 180 - tempAngle;
				if (pX - x < 0 && pY - y < 0) tempAngle = 180 + tempAngle;
				if (pX - x > 0 && pY - y < 0) tempAngle = 360 - tempAngle;
				float angle;
				if (tempAngle > 0) angle = 17.5f;
				if (tempAngle > 45) angle = 45;
				if (tempAngle > 90) angle = 135;
				if (tempAngle > 135) angle = 162.5f;
				if (tempAngle > 180) angle = 197.5f;
				if (tempAngle > 225) angle = 225;
				if (tempAngle > 270) angle = 315;
				if (tempAngle > 315) angle = 342.5f;
				CGameObjectsManager::GetInstance()->GetFireBall(x, y - 8, angle);
				hasShot = true;
			}
		}
	}
	
	if (pX < x) {
		if (pY < y) direction = 0;
		else direction = 1;
	}
	else {
		if (pY < y) direction = 2;
		else direction = 3;
	}
}

void CFirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PIRANHA_PLANT_WIDTH * 0.5f;
	top = y - PIRANHA_PLANT_HEIGHT * 0.5f;
	right = x + PIRANHA_PLANT_WIDTH * 0.5f;
	bottom = y + PIRANHA_PLANT_HEIGHT * 0.5f;
}