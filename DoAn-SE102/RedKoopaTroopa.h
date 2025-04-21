#pragma once
#include "Enemy.h"
#include "debug.h"
#include "EdgeSensor.h"

#define KOOPA_TROOPA_MOVE_SPEED 0.03f
#define KOOPA_TROOPA_SHELL_MOVE_SPEED 0.06f
#define KOOPA_TROOPA_DIE_JUMP_SPEED 0.06f
#define KOOPA_TROOPA_GRAVITY 0.0006f

#define KOOPA_TROOPA_WIDTH 16
#define KOOPA_TROOPA_HEIGHT 32
#define KOOPA_TROOPA_SHELL_HEIGHT 16

#define KOOPA_TROOPA_CHARGING_TIME 4000

//Ani Ids
#define RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT 90011
#define RED_KOOPA_TROOPA_ANIMATION_WALK_LEFT 90021
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE 90031
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING 90041
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_MOVING 90051
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE 90061
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING 90071
#define RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING 90081

enum KoopaTroopaState{OUTSIDE, SHELL_IDLE, SHELL_MOVING, K_DIE, K_DIE_KICKED};
enum KoopaTroopaDirection{NORMAL, UPSIDEDOWN};

class CRedKoopaTroopa : public CEnemy
{
	CEdgeSensor* edgeSensor;
	KoopaTroopaState state;
	KoopaTroopaDirection direction;
	float height;

	ULONGLONG charging_start;
public:
	CRedKoopaTroopa(float x, float y, int nx) : CEnemy(x, y, nx) {
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		state = KoopaTroopaState::OUTSIDE;
		//SetState(KoopaTroopaState::SHELL_IDLE);
		direction = KoopaTroopaDirection::NORMAL;
		height = KOOPA_TROOPA_HEIGHT;
		charging_start = CGame::GetInstance()->GetTickCount();

		edgeSensor = new CEdgeSensor(x, y - height * 0.5f - 1);
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsDead();

	KoopaTroopaState GetState() { return state; }
	void SetState(KoopaTroopaState state);
	void SetShellDirection(KoopaTroopaDirection direction) { this->direction = direction; }
	bool IsIdling() { return state == KoopaTroopaState::SHELL_IDLE; }
	void SetDirection(int nx);
};

