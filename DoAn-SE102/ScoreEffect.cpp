#include "ScoreEffect.h"

void CScoreEffect::Update(DWORD dt) {
	if (CGame::GetInstance()->GetTickCount() - existing_start > duration) isEnabled = false;
	if (!isEnabled) return;
	float tempVy = vy * (duration - (CGame::GetInstance()->GetTickCount() - existing_start)) / duration;
	y -= tempVy * dt;
}

void CScoreEffect::Render() {

	if (!isEnabled) return;
	if (CGame::GetInstance()->IsFrozen()) ani->Render1Frame(x, y);
	else ani->Render(x, y);
}

void CScoreEffect::ReEnable() {
	vy = SCORE_EFFECT_START_VY;
	LPGAME game = CGame::GetInstance();
	if (value != -1) game->IncreaseScore(value);
	else game->IncreaseLives(1);
	CEffect::ReEnable();
}

void CScoreEffect::SetValue(int x) {
	this->value = x;
	switch (value) {
	case 100:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_100);
		break;
	case 200:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_200);
		break;
	case 400:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_400);
		break;
	case 800:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_800);
		break;
	case 1000:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_1000);
		break;
	case 2000:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_2000);
		break;
	case 4000:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_4000);
		break;
	case 8000:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_8000);
		break;
	case -1:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_VP);
		break;
	default:
		ani = CAnimations::GetInstance()->Get(SCORE_EFFECT_VALUE_100);
		break;
	}
}
