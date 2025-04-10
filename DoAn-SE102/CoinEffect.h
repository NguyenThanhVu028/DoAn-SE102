#pragma once
#include "Effect.h"
#include "Game.h"
#include "GameObjectsManager.h"
#include "Animations.h"

#define DEFAULT_DURATION 575
#define COIN_EFFECT_MAX_HEIGHT 48

#define COIN_EFFECT_START_VY 0.3f
#define COINT_EFFECT_AY -0.001f

//Animation Ids
#define COIN_EFFECT_ANIMATION 30011

class CCoinEffect : public CEffect
{
	int value;
	float vy;
public:
	CCoinEffect(float x, float y, ULONGLONG duration = DEFAULT_DURATION, int value = 1) : CEffect(x, y, duration) { this->value = value; ani = CAnimations::GetInstance()->GetAsInstance(COIN_EFFECT_ANIMATION); ReEnable(); }
	void Update(DWORD dt);
	void Render();
	void ReEnable();
};

