#include "EnterablePipe.h"
#include "UIManager.h"

void CEnterablePipe::Update(DWORD dt) {
	if (decoy != NULL) {
		if (decoy->IsDeleted()) {
			delete decoy;
			decoy = NULL;
		}
		else decoy->Update(dt);
	}
	if (CGame::GetInstance()->GetTickCount() - enter_start > ENTER_TIME && entered && !enter_ended) {
		transition_start = CGame::GetInstance()->GetTickCount();
		enter_ended = true;
		CUIManager::GetInstance()->StartFading();
	}
	if (CGame::GetInstance()->GetTickCount() - transition_start > TRANSITION_TIME && enter_ended) {
		CGame::GetInstance()->InitiateSwitchScene(world_id);
	}
}

void CEnterablePipe::Render() {
	if (decoy != NULL) decoy->Render();
	CPipe::Render();
}

void CEnterablePipe::RequestEnter(bool direction) {
	if (!type) return;
	CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
	if (decoy == NULL && mario != NULL) {
		float pX, pY; mario->GetPosition(pX, pY);
		float realX = x + width * cellWidth * 0.5f, realY = y + height * 0.5f;
		//DebugOutTitle(L"realX %f", realX);
		if (pX < realX - ENTER_ZONE * 0.5f || pX > realX + ENTER_ZONE * 0.5f) return;
		if (direction && pY >= realY) return;
		if (!direction && pY <= realY) return;
		auto mario = CGameObjectsManager::GetInstance()->GetPlayer();
		if (decoy == NULL && mario != NULL) {
			decoy = new CMarioEnterPipeDecoy(pX, pY, direction);
			enter_start = CGame::GetInstance()->GetTickCount();
			entered = true;
		}
	}
}