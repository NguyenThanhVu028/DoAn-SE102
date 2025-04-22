#include "KoopaTroopa.h"
#include "Mario.h"

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - KOOPA_TROOPA_WIDTH * 0.5f;
	top = y - KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
	right = x + KOOPA_TROOPA_WIDTH * 0.5f;
	bottom = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
}

void CKoopaTroopa::Update(DWORD dt) {
	if (isKilled) return;
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
	if (dynamic_cast<CMario*>(e->src_obj)) {
		OnCollisionWithMario(e);
	}
	if (dynamic_cast<CEnemy*>(e->obj)) {
		OnCollisionWithOtherEnemy(e);
	}
}

void CKoopaTroopa::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	if (IsDead()) return;
	switch (state) {
	case KoopaTroopaState::OUTSIDE:
		if (e->ny < 0) SetState(KoopaTroopaState::SHELL_IDLE);
		break;
	case KoopaTroopaState::SHELL_IDLE:
		if (!isHeld) {
			CMario* player = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
			if (player->IsRunButtonPressed()) {
				if (e->ny < 0) {
					float pX, pY;
					player->GetPosition(pX, pY);
					vx = (pX < x) ? KOOPA_TROOPA_SHELL_MOVE_SPEED : -KOOPA_TROOPA_SHELL_MOVE_SPEED;
					SetState(KoopaTroopaState::SHELL_MOVING);
				}
			}
			else {
				float pX, pY;
				player->GetPosition(pX, pY);
				vx = (pX < x) ? KOOPA_TROOPA_SHELL_MOVE_SPEED : -KOOPA_TROOPA_SHELL_MOVE_SPEED;
				SetState(KoopaTroopaState::SHELL_MOVING);
			}

		}
		//if the shell is being held, not check collision with Mario
		break;
	case KoopaTroopaState::SHELL_MOVING:
		break;
	}
}

void CKoopaTroopa::OnCollisionWithOtherEnemy(LPCOLLISIONEVENT e) {
	if ((state == KoopaTroopaState::SHELL_IDLE && isHeld) || state == KoopaTroopaState::SHELL_MOVING)
		dynamic_cast<CEnemy*>(e->obj)->OnCollisionWithShell(e);
}

void CKoopaTroopa::OnCollisionWithShell(LPCOLLISIONEVENT e) {
	SetState(KoopaTroopaState::K_DIE_KICKED);
	float oX, oY;
	e->obj->GetPosition(oX, oY);
	vx = (oX < x) ? KOOPA_TROOPA_DIE_MOVE_SPEED : -KOOPA_TROOPA_DIE_MOVE_SPEED;
}

bool CKoopaTroopa::IsDead() {
	return (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED || !isEnabled);
}

void CKoopaTroopa::SetState(KoopaTroopaState state) {
	height = KOOPA_TROOPA_SHELL_HEIGHT;
	untouchable_start = CGame::GetInstance()->GetTickCount();
	switch (state) {
	case KoopaTroopaState::OUTSIDE:
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		height = KOOPA_TROOPA_HEIGHT;
		break;
	case KoopaTroopaState::SHELL_IDLE:
		isHeld = false;
		charging_start = CGame::GetInstance()->GetTickCount();
		vx = 0;
		break;
	case KoopaTroopaState::K_DIE:
		vx = 0;
		vy = -KOOPA_TROOPA_DIE_JUMP_SPEED;
		break;
	case KoopaTroopaState::K_DIE_KICKED:
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

bool CKoopaTroopa::IsUntouchable() { return CGame::GetInstance()->GetTickCount() - untouchable_start < KOOPA_TROOPA_UNTOUCHABLE_TIME; }

void CKoopaTroopa::SetEnable(bool t) { 
	vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
	ax = 0;
	vy = 0;
	ay = KOOPA_TROOPA_GRAVITY;
	state = KoopaTroopaState::OUTSIDE;
	shellDirection = KoopaTroopaShellDirection::NORMAL;
	height = KOOPA_TROOPA_HEIGHT;
	charging_start = CGame::GetInstance()->GetTickCount();
	isHeld = false;
	isEnabled = t; 
}