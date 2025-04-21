#include "RedKoopaTroopa.h"
#include "GameObjectsManager.h"

void CRedKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - KOOPA_TROOPA_WIDTH * 0.5f;
	top = y - KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
	right = x + KOOPA_TROOPA_WIDTH * 0.5f;
	bottom = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
}

void CRedKoopaTroopa::Render() {

	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - KOOPA_TROOPA_WIDTH * 0.5f - DESPAWN_OFFSET || x > cX + screenWidth + KOOPA_TROOPA_WIDTH * 0.5f + DESPAWN_OFFSET) {
		if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) isKilled = true;
		else isEnabled = false;
		return;
	}
	if (y < cY - KOOPA_TROOPA_HEIGHT * 0.5f - DESPAWN_OFFSET || y > cY + screenHeight + KOOPA_TROOPA_HEIGHT * 0.5f + DESPAWN_OFFSET) {
		if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) isKilled = true;
		else isEnabled = false;
		return;
	}

	int aniToRender = RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT;
	switch (state) {
	case KoopaTroopaState::K_DIE:
	case KoopaTroopaState::K_DIE_KICKED:
		aniToRender = (direction == KoopaTroopaDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		break;
	case KoopaTroopaState::OUTSIDE:
		aniToRender = (vx > 0) ? RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT : RED_KOOPA_TROOPA_ANIMATION_WALK_LEFT;
		break;
	case KoopaTroopaState::SHELL_IDLE:
		if (CGame::GetInstance()->GetTickCount() - charging_start < KOOPA_TROOPA_CHARGING_TIME * 0.75f)
			aniToRender = (direction == KoopaTroopaDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		else if (CGame::GetInstance()->GetTickCount() - charging_start <= KOOPA_TROOPA_CHARGING_TIME)
			aniToRender = (direction == KoopaTroopaDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING;
		break;
	case KoopaTroopaState::SHELL_MOVING:
		aniToRender = (direction == KoopaTroopaDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_MOVING : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING;
		break;
	}
	if (CGame::GetInstance()->IsFrozen())
		CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(x, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
	else CAnimations::GetInstance()->Get(aniToRender)->Render(x, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
}

void CRedKoopaTroopa::Update(DWORD dt) {
	if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) {
		vy += ay * dt;
		y += vy * dt;
		x += vx * dt;
		return;
	}

	if (CGame::GetInstance()->GetTickCount() - charging_start > KOOPA_TROOPA_CHARGING_TIME && state == KoopaTroopaState::SHELL_IDLE) SetState(KoopaTroopaState::OUTSIDE);

	vy += ay * dt;

	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0);
}

void CRedKoopaTroopa::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CRedKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->obj == this) return;
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
}

bool CRedKoopaTroopa::IsDead() {
	return false;
}

void CRedKoopaTroopa::SetState(KoopaTroopaState state){
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