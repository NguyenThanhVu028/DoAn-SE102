#pragma once
#include "Effect.h"
#include "Animations.h"
#define WHACK_EFFECT_DEFAULT_DURATION 200

//Ani Ids
#define WHACK_EFFECT_ANIMATION 30041
class CWhackEffect : public CEffect
{
public:
	CWhackEffect(float x, float y, ULONGLONG duration = WHACK_EFFECT_DEFAULT_DURATION) : CEffect(x, y, duration){
		ani = CAnimations::GetInstance()->Get(WHACK_EFFECT_ANIMATION);
		ani->SetDuration(WHACK_EFFECT_DEFAULT_DURATION);
	}
	void Render();
};

