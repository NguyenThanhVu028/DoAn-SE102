#pragma once
#include "Enemy.h"

#define KOOPA_TROOPA_MOVE_SPEED 0.03f
#define KOOPA_TROOPA_SHELL_MOVE_SPEED 0.06f
#define KOOPA_TROOPA_DIE_JUMP_SPEED 0.06f
#define KOOPA_TROOPA_GRAVITY 0.0006f

#define KOOPA_TROOPA_WIDTH 16
#define KOOPA_TROOPA_HEIGHT 32
#define KOOPA_TROOPA_SHELL_HEIGHT 16

#define KOOPA_TROOPA_CHARGING_TIME 4000

enum KoopaTroopaState { OUTSIDE, SHELL_IDLE, SHELL_MOVING, K_DIE, K_DIE_KICKED };
enum KoopaTroopaDirection { NORMAL, UPSIDEDOWN };

class CKoopaTroopa : public CEnemy
{
protected:
	KoopaTroopaState state;
	KoopaTroopaDirection direction;
	float height;

	ULONGLONG charging_start;
public:
	CKoopaTroopa(float x, float y, int nx) : CEnemy(x, y, nx) {
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		state = KoopaTroopaState::OUTSIDE;
		direction = KoopaTroopaDirection::NORMAL;
		height = KOOPA_TROOPA_HEIGHT;
		charging_start = CGame::GetInstance()->GetTickCount();
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render() = 0;
	virtual void Update(DWORD dt);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual bool IsDead();

	KoopaTroopaState GetState() { return state; }
	virtual void SetState(KoopaTroopaState state);
	void SetShellDirection(KoopaTroopaDirection direction) { this->direction = direction; }
	bool IsIdling() { return state == KoopaTroopaState::SHELL_IDLE; }
	virtual void SetDirection(int nx);

};

