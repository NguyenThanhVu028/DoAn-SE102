#include "Effect.h"
void CEffect::ReEnable() {
	isEnabled = true;
	if (ani != NULL) ani->Reset();
	existing_start = GetTickCount64();
}