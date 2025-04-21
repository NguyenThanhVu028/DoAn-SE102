#include "CoinQuestionBlock.h"

void CCoinQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!IsInteractable()) return;
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		if (e->ny > 0) {
			bounce_time_start = CGame::GetInstance()->GetTickCount();
			isAvailable = false;
			CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
		}
	}
}