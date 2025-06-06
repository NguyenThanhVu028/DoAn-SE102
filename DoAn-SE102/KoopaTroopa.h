#pragma once
#include "Enemy.h"

#define KOOPA_TROOPA_MOVE_SPEED 0.03f
#define KOOPA_TROOPA_SHELL_MOVE_SPEED 0.225f
#define KOOPA_TROOPA_DIE_JUMP_SPEED 0.2f
#define KOOPA_TROOPA_DIE_MOVE_SPEED 0.01f
#define KOOPA_TROOPA_GRAVITY 0.0006f

#define KOOPA_TROOPA_WIDTH 16
#define KOOPA_TROOPA_HEIGHT 32
#define KOOPA_TROOPA_SHELL_HEIGHT 16

#define KOOPA_TROOPA_CHARGING_TIME 10000
#define KOOPA_TROOPA_CHARGING_TIME_PROPORTION 0.75f
#define KOOPA_TROOPA_UNTOUCHABLE_TIME 200

#define KOOPA_TROOPA_SHAKING_FREQUENCY 30
#define KOOPA_TROOPA_SHAKING_INTENSITY 0.5f

enum KoopaTroopaState { OUTSIDE, SHELL_IDLE, SHELL_MOVING, K_DIE, K_DIE_KICKED };
enum KoopaTroopaShellDirection { NORMAL, UPSIDEDOWN };

class CKoopaTroopa : public CEnemy
{
protected:
	KoopaTroopaState state;
	KoopaTroopaShellDirection shellDirection;
	float height;
	CAnimation* aniToRender = NULL;

	ULONGLONG charging_start;

	bool isHeld;

	int streak;
public:
	CKoopaTroopa(float x, float y, int nx) : CEnemy(x, y, nx) {
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		state = KoopaTroopaState::OUTSIDE;
		shellDirection = KoopaTroopaShellDirection::NORMAL;
		height = KOOPA_TROOPA_HEIGHT;
		charging_start = CGame::GetInstance()->GetTickCount();
		isHeld = false;
		streak = 1;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();				//Check conditions to call RealRender function
	virtual void RealRender() {};		//Real render function for KoopaTroopa, Mario can use this function to determine the order of shell's rendering
	virtual void Update(DWORD dt);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithMario(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithOtherEnemy(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithShell(LPCOLLISIONEVENT e);
	void OnCollisionWithMarioTail(LPCOLLISIONEVENT e);
	virtual bool IsDead();
	virtual void SetEnable(bool t);

	KoopaTroopaState GetState() { return state; }
	virtual void SetState(KoopaTroopaState state);
	void SetShellDirection(KoopaTroopaShellDirection direction) { this->shellDirection = direction; }
	bool IsIdling() { return state == KoopaTroopaState::SHELL_IDLE; }
	bool IsMoving() { return state == KoopaTroopaState::SHELL_MOVING; }
	bool IsHeld() { return isHeld; }
	virtual void SetDirection(int nx);
	bool IsUntouchable() override;
	void OnHeld() { isHeld = true; ay = 0; vy = 0; }
	void ReleaseHeld() { isHeld = false; ay = KOOPA_TROOPA_GRAVITY; }
};

