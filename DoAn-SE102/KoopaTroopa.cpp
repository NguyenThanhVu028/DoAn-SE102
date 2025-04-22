#include "KoopaTroopa.h"

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - KOOPA_TROOPA_WIDTH * 0.5f;
	top = y - KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
	right = x + KOOPA_TROOPA_WIDTH * 0.5f;
	bottom = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
}

void CKoopaTroopa::Update(DWORD dt) {
	if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) {
		vy += ay * dt;
		y += vy * dt;
		x += vx * dt;
		return;
	}

	if (CGame::GetInstance()->GetTickCount() - charging_start > KOOPA_TROOPA_CHARGING_TIME && state == KoopaTroopaState::SHELL_IDLE) SetState(KoopaTroopaState::OUTSIDE);

	vy += ay * dt;
}

void CKoopaTroopa::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
}

bool CKoopaTroopa::IsDead() {
	return false;
}

void CKoopaTroopa::SetState(KoopaTroopaState state) {
	height = KOOPA_TROOPA_SHELL_HEIGHT;
	switch (state) {
	case KoopaTroopaState::OUTSIDE:
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		height = KOOPA_TROOPA_HEIGHT;
		break;
	case KoopaTroopaState::SHELL_IDLE:
		vx = 0;
		break;
	case KoopaTroopaState::K_DIE:
		vx = 0;
		vy = -KOOPA_TROOPA_DIE_JUMP_SPEED;
		break;
	}
	this->state = state;
}

void CKoopaTroopa::SetDirection(int nx) {
	CMovableGameObject::SetDirection(nx);
	if (nx == 1) vx = KOOPA_TROOPA_MOVE_SPEED;
	else vx = -KOOPA_TROOPA_MOVE_SPEED;
}