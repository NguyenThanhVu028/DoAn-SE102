#include "CoinEffect.h"

void CCoinEffect::Update(DWORD dt) {
	if (CGame::GetInstance()->GetTickCount() - existing_start > duration) {
		if (isEnabled) {
			CGameObjectsManager::GetInstance()->GetScoreEffect(x, y, 100);
			isEnabled = false;
		}
	}
	if (!isEnabled) return;
	vy += COINT_EFFECT_AY * dt;
	y -= vy * dt;
}

void CCoinEffect::Render() {
	if (!isEnabled) return;
	if (CGame::GetInstance()->IsFrozen()) ani->Render1Frame(x, y);
	else ani->Render(x, y);
}

void CCoinEffect::ReEnable() {
	vy = COIN_EFFECT_START_VY;
	LPGAME game = CGame::GetInstance();
	game->IncreaseCoin(value);
	CEffect::ReEnable();
}
