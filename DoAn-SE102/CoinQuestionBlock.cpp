#include "CoinQuestionBlock.h"

void CCoinQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!IsInteractable()) return;
	auto game = CGame::GetInstance();
	float cX, cY;
	int screenWidth = game->GetBackBufferWidth(), screenHeight = game->GetBackBufferHeight();
	game->GetCamPos(cX, cY);
	if (x < cX || x > cX + screenWidth || y < cY || y > cY + screenHeight) {
		bounce_time_start = CGame::GetInstance()->GetTickCount();
		return;
	}
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		if (e->ny > 0) {
			bounce_time_start = CGame::GetInstance()->GetTickCount();
			isAvailable = false;
			CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
		}
	}
	if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
		bounce_time_start = CGame::GetInstance()->GetTickCount();
		isAvailable = false;
		CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
	}
}