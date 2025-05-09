#pragma once
#include "Effect.h"
#include "Animations.h"
#define SMOKE_EFFECT_DEFAULT_DURATION 200

//Ani Id
#define SMOKE_EFFECT_ANIMATION 30051
class CSmokeEffect : public CEffect
{
public:
	CSmokeEffect(float x, float y, ULONGLONG duration = SMOKE_EFFECT_DEFAULT_DURATION) : CEffect(x, y, duration) {
		ani = CAnimations::GetInstance()->Get(SMOKE_EFFECT_ANIMATION);
		ani->SetDuration(SMOKE_EFFECT_DEFAULT_DURATION);
	}
	void Render();
};

