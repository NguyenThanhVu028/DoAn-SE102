#pragma once
#include "Pipe.h"
#include "NormalPiranhaPlant.h"

class CNormalPiranhaPlantPipe : public CPipe
{
	CNormalPiranhaPlant* plant = NULL;
	int type;
public:
	CNormalPiranhaPlantPipe(float x, float y, float cellWidth, float cellHeight, int length, bool isVertical, int side, int type) : CPipe(x, y, cellWidth, cellHeight, length, isVertical, side) {
		this->type = type;
		switch (type) {
		case NORMAL_PIRANHA_PLANT_GREEN:
			plant = new CNormalPiranhaPlant(this->x + cellWidth * width * 0.5f, this->y + PIRANHA_PLANT_HEIGHT * 0.5f + 1, NORMAL_PIRANHA_PLANT_GREEN);
			//CGameObjectsManager::GetInstance()->AddMovableObject(plant);
			break;
		case NORMAL_PIRANHA_PLANT_RED:
			plant = new CNormalPiranhaPlant(this->x + cellWidth * width * 0.5f, this->y + PIRANHA_PLANT_HEIGHT * 0.5f + 1, NORMAL_PIRANHA_PLANT_RED);
			//CGameObjectsManager::GetInstance()->AddMovableObject(plant);
			break;
		}
	}
	void Update(DWORD dt);
	void Render();
};

