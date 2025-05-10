#include "CoinQuestionBlock.h"

void CCoinQuestionBlock::SpecialEffect(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMarioHead*>(e->src_obj)) {
		isAvailable = false;
		CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
	}
	if (dynamic_cast<CKoopaTroopa*>(e->src_obj)) {
		isAvailable = false;
		CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
	}
	if (dynamic_cast<CMarioTail*>(e->src_obj)) {
		isAvailable = false;
		CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16, 1);
	}
}