#include "RedKoopaTroopa.h"
#include "GameObjectsManager.h"

void CRedKoopaTroopa::Render() {
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
	CKoopaTroopa::Update(dt);

	edgeSensor->x = x; edgeSensor->y = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f - edgeSensor->height * 0.5f;
	edgeSensor->SetSpeed(vx, vy);
	edgeSensor->ProcessCollision(dt);

	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0);
	if ((!edgeSensor->RightEdge() && vx > 0) || (!edgeSensor->LeftEdge() && vx < 0)) vx = -vx;
}

void CRedKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	CKoopaTroopa::OnCollisionWith(e);
}

bool CRedKoopaTroopa::IsDead() {
	return false;
}