#include "FirePiranhaPlant.h"
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
	DebugOutTitle(L"Direction: %d %d %d", type, IsRising(), aniToRender);
	CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
}

void CFirePiranhaPlant::Update(DWORD dt) {
	CPiranhaPlant::Update(dt);
	float pX, pY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
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