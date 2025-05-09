#pragma once
#include "Game.h"
#include "Effect.h"
#include "Animations.h"

#define SCORE_EFFECT_DEFAULT_DURATION 600

#define SCORE_EFFECT_START_VY 0.075f
//Animation Ids
#define SCORE_EFFECT_VALUE_100 30021
#define SCORE_EFFECT_VALUE_200 30022
#define SCORE_EFFECT_VALUE_400 30023
#define SCORE_EFFECT_VALUE_800 30024
#define SCORE_EFFECT_VALUE_1000 30025
#define SCORE_EFFECT_VALUE_2000 30026
#define SCORE_EFFECT_VALUE_4000 30027
#define SCORE_EFFECT_VALUE_8000 30028
#define SCORE_EFFECT_VALUE_VP 30029

class CScoreEffect : public CEffect
{
	int value;
	float vy;
public:
	CScoreEffect(float x, float y, int value = 100, ULONGLONG duration = SCORE_EFFECT_DEFAULT_DURATION) : CEffect(x, y, duration) {
		SetValue(value);
		ReEnable();
	}
	void Update(DWORD dt);
	void Render();
	void ReEnable();
	void SetValue(int x);
};

