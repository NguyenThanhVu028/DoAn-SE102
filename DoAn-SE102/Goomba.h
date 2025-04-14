#pragma once
#include "Enemy.h"

#define GOOMBA_WIDTH 16
#define GOOMBA_HEIGHT 16

#define GOOMBA_MOVING_SPEED 0.05f
#define GOOMBA_JUMP_DEFLECT_SPEED 0.2f;

#define GOOMBA_GRAVITY 0.0006f

#define GOOMBA_DEAD_TIME 500

//Animation Ids
#define GOOMBA_ANIMATION_WALKING 80101
#define GOOMBA_ANIMATION_FLATTENED 80111
#define GOOMBA_ANIMATION_UPSIDE_DOWN 80121

enum GoombaState {ALIVE, FLATTENED, UPSIDE_DOWN};

class CGoomba : public CEnemy
{
	GoombaState state;
	ULONGLONG dead_start;
public:
	CGoomba(float x, float y, int nx = 1) : CEnemy(x, y, nx) {
		state = GoombaState::ALIVE;
		vx = (nx == 1) ? GOOMBA_MOVING_SPEED : -GOOMBA_MOVING_SPEED;
		ay = GOOMBA_GRAVITY;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	bool IsDead();
	void SetState(GoombaState state, int nx = 0);

	void SetDirection(int nx);
};

