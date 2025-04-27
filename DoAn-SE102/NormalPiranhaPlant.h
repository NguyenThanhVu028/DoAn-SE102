#pragma once
#include "PiranhaPlant.h"

#define NORMAL_PIRANHA_PLANT_GREEN 0
#define NORMAL_PIRANHA_PLANT_RED 1

#define NORMAL_PIRANHA_PLANT_GREEN_RISING_HEIGHT 24
#define NORMAL_PIRANHA_PLANT_RED_RISING_HEIGHT 32

#define NORMAL_PIRANHA_PLANT_RISING_TIME 500
#define NORMAL_PIRANHA_PLANT_WAITING_TIME 1000

//Animation Ids
#define NORMAL_PIRANHA_GREEN_ANIMATION_RISING 50011
#define NORMAL_PIRANHA_RED_ANIMATION_RISING 50021

class CNormalPiranhaPlant : public CPiranhaPlant 
{
	int type;
public:
	CNormalPiranhaPlant(float x, float y, int type) : CPiranhaPlant(x, y) {
		this->type = type;
		switch (type) {
		case NORMAL_PIRANHA_PLANT_GREEN:
			risingHeight = NORMAL_PIRANHA_PLANT_GREEN_RISING_HEIGHT;
			break;
		case NORMAL_PIRANHA_PLANT_RED:
			risingHeight = NORMAL_PIRANHA_PLANT_RED_RISING_HEIGHT;
			break;
		}
		risingTime = NORMAL_PIRANHA_PLANT_RISING_TIME;
		waitingTime = NORMAL_PIRANHA_PLANT_WAITING_TIME;
	}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

