#include "KoopaTroopa.h"
#include "Mario.h"
#include "QuestionBlock.h"

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - KOOPA_TROOPA_WIDTH * 0.5f;
	bottom = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f;
	top = y - KOOPA_TROOPA_SHELL_HEIGHT * 0.5f + 1;
	right = left + KOOPA_TROOPA_WIDTH;
	
}

void CKoopaTroopa::Render() {
	if (!isEnabled || isKilled) return;

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

	if (isHeld) return;

	RealRender();
}

void CKoopaTroopa::Update(DWORD dt) {
	if (isKilled || !isEnabled) return;
	if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) {
		vy += ay * dt;
		y += vy * dt;
		x += vx * dt;
		return;
	}

	if (CGame::GetInstance()->GetTickCount() - charging_start > KOOPA_TROOPA_CHARGING_TIME && state == KoopaTroopaState::SHELL_IDLE) {
		SetState(KoopaTroopaState::OUTSIDE);
		SetDirection(KoopaTroopaShellDirection::NORMAL);
	}
	if (state == KoopaTroopaState::SHELL_IDLE && vy == 0) vx = 0;
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
	else if (dynamic_cast<CEnemy*>(e->obj)) {
		OnCollisionWithOtherEnemy(e);
	}
	else {
		if (e->isOverlap && !e->obj->AllowOverlap() && !isHeld && state != KoopaTroopaState::OUTSIDE) {
			SetShellDirection(KoopaTroopaShellDirection::UPSIDEDOWN);
			SetState(KoopaTroopaState::K_DIE);
		}
		if (state == KoopaTroopaState::SHELL_MOVING) 
			e->obj->OnCollisionWith(e);
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
		if (e->ny < 0) SetState(KoopaTroopaState::SHELL_IDLE);
		break;
	}
}

void CKoopaTroopa::OnCollisionWithOtherEnemy(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CEnemy*>(e->obj)->IsDead() || !dynamic_cast<CEnemy*>(e->obj)->IsEnabled()) return;
	if ((state == KoopaTroopaState::SHELL_IDLE && isHeld) || state == KoopaTroopaState::SHELL_MOVING) {
		if(isHeld) {
			SetState(KoopaTroopaState::K_DIE_KICKED);
			SetShellDirection(KoopaTroopaShellDirection::UPSIDEDOWN);
			float oX, oY;
			if (e->obj != this) {
				e->obj->GetPosition(oX, oY);
				
			}
			else e->src_obj->GetPosition(oX, oY);
			vx = (oX < x) ? KOOPA_TROOPA_DIE_MOVE_SPEED : -KOOPA_TROOPA_DIE_MOVE_SPEED;
		}
		if(e->obj != this)dynamic_cast<CEnemy*>(e->obj)->OnCollisionWithShell(e);
		float oX, oY; e->obj->GetPosition(oX, oY);
		if(streak < 9)
			CGameObjectsManager::GetInstance()->GetScoreEffect(oX, oY, 100 * streak);
		else CGameObjectsManager::GetInstance()->GetScoreEffect(oX, oY, -1);
		streak++;

	}

}

void CKoopaTroopa::OnCollisionWithShell(LPCOLLISIONEVENT e) {
	SetState(KoopaTroopaState::K_DIE_KICKED);
	SetShellDirection(KoopaTroopaShellDirection::UPSIDEDOWN);
	float oX, oY;
	e->obj->GetPosition(oX, oY);
	vx = (oX < x) ? KOOPA_TROOPA_DIE_MOVE_SPEED : -KOOPA_TROOPA_DIE_MOVE_SPEED;
	CGameObjectsManager::GetInstance()->GetWhackEffect(x, y);

}

void CKoopaTroopa::OnCollisionWithMarioTail(LPCOLLISIONEVENT e) {
	untouchable_start = CGame::GetInstance()->GetTickCount();
	SetState(KoopaTroopaState::SHELL_IDLE);
	SetShellDirection(KoopaTroopaShellDirection::UPSIDEDOWN);
	float oX, oY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(oX, oY);
	vx = (oX < x) ? KOOPA_TROOPA_MOVE_SPEED * 1.5f : -KOOPA_TROOPA_MOVE_SPEED * 1.5f;
	vy = -KOOPA_TROOPA_DIE_JUMP_SPEED;
	CGameObjectsManager::GetInstance()->GetWhackEffect(x, y);
}

bool CKoopaTroopa::IsDead() {
	return (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED || !isEnabled);
}

void CKoopaTroopa::SetState(KoopaTroopaState state) {
	streak = 1;
	height = KOOPA_TROOPA_SHELL_HEIGHT;
	this->state = state;
	if(state != KoopaTroopaState::OUTSIDE) untouchable_start = CGame::GetInstance()->GetTickCount();
	//else untouchable_start = CGame::GetInstance()->GetTickCount() - KOOPA_TROOPA_UNTOUCHABLE_TIME * 0.0005f;
	switch (state) {
	case KoopaTroopaState::OUTSIDE:
		vx = (nx == 1) ? KOOPA_TROOPA_MOVE_SPEED : -KOOPA_TROOPA_MOVE_SPEED;
		ax = 0;
		vy = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		height = KOOPA_TROOPA_HEIGHT;
		shellDirection = KoopaTroopaShellDirection::NORMAL;
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