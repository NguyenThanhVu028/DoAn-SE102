#pragma once
#include "KoopaTroopa.h"
#include "Enemy.h"
#include "debug.h"

#define GREEN_KOOPATROOPA_JUMP_SPEED 0.22f
#define GREEN_KOOPATROOPA_WING_POSITION_OFFSET_X 4
#define GREEN_KOOPATROOPA_WING_POSITION_OFFSET_Y 11

//Ani Ids
#define GREEN_KOOPA_TROOPA_ANIMATION_WALK_RIGHT 90091
#define GREEN_KOOPA_TROOPA_ANIMATION_WALK_LEFT 90101
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_IDLE 90111
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING 90121
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_MOVING 90131
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE 90141
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING 90151
#define GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING 90161
#define GREEN_KOOPA_TROOPA_ANIMATION_WING_RIGHT 90171
#define GREEN_KOOPA_TROOPA_ANIMATION_WING_LEFT 90181

class CGreenKoopaTroopa : public CKoopaTroopa
{
	bool hasWingOri;
	bool hasWing;
public:
	CGreenKoopaTroopa(float x, float y, int nx, bool hasWing):CKoopaTroopa(x, y, nx){
		this->hasWingOri = hasWing;
		this->hasWing = hasWing;
	}
	void Render();
	void RealRender();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	void SetEnable(bool t);
};

