#pragma once
#include "KoopaTroopa.h"
#include "Enemy.h"
#include "debug.h"
#include "EdgeSensor.h"

//Ani Ids
#define RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT 90011
#define RED_KOOPA_TROOPA_ANIMATION_WALK_LEFT 90021
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE 90031
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING 90041
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_MOVING 90051
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE 90061
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING 90071
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING 90081

class CRedKoopaTroopa : public CKoopaTroopa
{
	CEdgeSensor* edgeSensor;
public:
	CRedKoopaTroopa(float x, float y, int nx) : CKoopaTroopa(x, y, nx) {
		edgeSensor = new CEdgeSensor(x, y - height * 0.5f - 1);
	}

	void Render();
	void RealRender();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	KoopaTroopaState GetState() { return state; }
};

