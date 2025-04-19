#include "NormalPiranhaPlantPipe.h"
void CNormalPiranhaPlantPipe::Update(DWORD dt) {
	if (plant != NULL) {
		if (plant->IsDeleted()) {
			delete plant;
			plant = NULL;
			return;
		}
	}

	float pL, pT, pR, pB;
	float L, T, R, B;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetBoundingBox(pL, pT, pR, pB);
	GetBoundingBox(L, T, R, B);
	if ((pL > R || pR < L)) {
		if (plant != NULL) {
			plant->SetActive(true);
		}
	}
	else if (plant != NULL) plant->SetActive(false);
	if (plant != NULL) plant->Update(dt);
}

void CNormalPiranhaPlantPipe::Render() {
	if (plant != NULL) plant->Render();
	CPipe::Render();
}