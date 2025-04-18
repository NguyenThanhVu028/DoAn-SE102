#include "Effect.h"
#include "Game.h"
void CEffect::ReEnable() {
	isEnabled = true;
	if (ani != NULL) ani->Reset();
	existing_start = CGame::GetInstance()->GetTickCount();
}