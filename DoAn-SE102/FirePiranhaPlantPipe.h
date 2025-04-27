#pragma once
#include "Pipe.h"
#include "FirePiranhaPlant.h"
class CFirePiranhaPlantPipe : public CPipe
{
	CFirePiranhaPlant* plant = NULL;
	int type;
public:
	CFirePiranhaPlantPipe(float x, float y, float cellWidth, float cellHeight, int length, bool isVertical, int side, int type) : CPipe(x, y, cellWidth, cellHeight, length, isVertical, side) {
		this->type = type;
		switch (type) {
		case FIRE_PIRANHA_PLANT_GREEN:
			plant = new CFirePiranhaPlant(this->x + cellWidth * width * 0.5f, this->y + PIRANHA_PLANT_HEIGHT * 0.5f, FIRE_PIRANHA_PLANT_GREEN);
			break;
		case FIRE_PIRANHA_PLANT_RED:
			plant = new CFirePiranhaPlant(this->x + cellWidth * width * 0.5f, this->y + PIRANHA_PLANT_HEIGHT * 0.5f, FIRE_PIRANHA_PLANT_RED);
			break;
		}
		//CGameObjectsManager::GetInstance()->AddMovableObject(plant);
	}
	void Update(DWORD dt);
	void Render();
};

