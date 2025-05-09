#include "WhackEffect.h"
void CWhackEffect::Render() {
	if (!isEnabled) return;
	if (CGame::GetInstance()->IsFrozen()) ani->Render1Frame(x, y);
	else ani->RenderByDuration(x, y);
}