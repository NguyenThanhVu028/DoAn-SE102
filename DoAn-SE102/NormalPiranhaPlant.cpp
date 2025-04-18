#include "NormalPiranhaPlant.h"

void CNormalPiranhaPlant::Render() {
	if (type == NORMAL_PIRANHA_PLANT_GREEN) {
		if (CGame::GetInstance()->IsFrozen())
			CAnimations::GetInstance()->Get(NORMAL_PIRANHA_GREEN_ANIMATION_RISING)->Render1Frame(x, y);
		else CAnimations::GetInstance()->Get(NORMAL_PIRANHA_GREEN_ANIMATION_RISING)->Render(x, y);
	}
	else if (type == NORMAL_PIRANHA_PLANT_RED) {
		if (CGame::GetInstance()->IsFrozen())
			CAnimations::GetInstance()->Get(NORMAL_PIRANHA_RED_ANIMATION_RISING)->Render1Frame(x, y);
		else CAnimations::GetInstance()->Get(NORMAL_PIRANHA_RED_ANIMATION_RISING)->Render(x, y);
	}
}

void CNormalPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PIRANHA_PLANT_WIDTH * 0.5f;
	top = y - PIRANHA_PLANT_HEIGHT * 0.5f;
	right = x + PIRANHA_PLANT_WIDTH * 0.5f;
	bottom = y + PIRANHA_PLANT_HEIGHT * 0.5f;
}
