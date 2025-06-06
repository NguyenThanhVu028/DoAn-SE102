#include "FirePiranhaPlantPipe.h"
void CFirePiranhaPlantPipe::Update(DWORD dt) {
	if(plant!= NULL)
		if (plant->IsKilled()) {
			delete plant;
			plant = NULL;
		}
	float pL, pT, pR, pB;
	float L, T, R, B;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetBoundingBox(pL, pT, pR, pB);
	GetBoundingBox(L, T, R, B);
	if ((pL > R + PIPE_ACTIVE_ZONE_OFFSET || pR < L - PIPE_ACTIVE_ZONE_OFFSET)) {
		if (plant != NULL) {
			plant->SetActive(true);
		}
	}
	else if (plant != NULL) plant->SetActive(false);
	if (plant != NULL) plant->Update(dt);

}

void CFirePiranhaPlantPipe::Render() {
	if (plant != NULL) plant->Render();
	CPipe::Render();
}
