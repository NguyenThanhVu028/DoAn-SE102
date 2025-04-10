#include "CoinEffect.h"

void CCoinEffect::Update(DWORD dt) {
	if (!isEnabled) return;
	vy += COINT_EFFECT_AY * dt;
	y -= vy * dt;
}

void CCoinEffect::Render() {
	if (GetTickCount64() - existing_start > duration) {
		if (isEnabled) {
			CGameObjectsManager::GetInstance()->GetScoreEffect(x, y, 100);
			isEnabled = false;
		}
	}
	if (!isEnabled) return;
	ani->Render(x, y);
}

void CCoinEffect::ReEnable() {
	vy = COIN_EFFECT_START_VY;
	LPGAME game = CGame::GetInstance();
	game->IncreaseCoin(value);
	CEffect::ReEnable();
}
