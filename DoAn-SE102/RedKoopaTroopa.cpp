#include "RedKoopaTroopa.h"
#include "GameObjectsManager.h"

void CRedKoopaTroopa::Update(DWORD dt) {
	if (isKilled || !isEnabled) return;
	CKoopaTroopa::Update(dt);

	edgeSensor->x = x; edgeSensor->y = y + KOOPA_TROOPA_SHELL_HEIGHT * 0.5f - edgeSensor->height * 0.5f;
	edgeSensor->SetSpeed(vx, vy);
	edgeSensor->ProcessCollision(dt);

	if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) return;
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0);
	if (((!edgeSensor->RightEdge() && vx > 0) || (!edgeSensor->LeftEdge() && vx < 0)) && state == KoopaTroopaState::OUTSIDE) vx = -vx;
}

void CRedKoopaTroopa::RealRender() {
	if (aniToRender == NULL) aniToRender = CAnimations::GetInstance()->Get(RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT);
	int Id = RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT;
	switch (state) {
	case KoopaTroopaState::K_DIE:
	case KoopaTroopaState::K_DIE_KICKED:
		Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		break;
	case KoopaTroopaState::OUTSIDE:
		Id = (vx > 0) ? RED_KOOPA_TROOPA_ANIMATION_WALK_RIGHT : RED_KOOPA_TROOPA_ANIMATION_WALK_LEFT;
		break;
	case KoopaTroopaState::SHELL_IDLE:
		if (CGame::GetInstance()->GetTickCount() - charging_start < KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION)
			Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		else if (CGame::GetInstance()->GetTickCount() - charging_start <= KOOPA_TROOPA_CHARGING_TIME)
			Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING;
		break;
	case KoopaTroopaState::SHELL_MOVING:
		Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? RED_KOOPA_TROOPA_ANIMATION_SHELL_MOVING : RED_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING;
		break;
	}
	aniToRender = CAnimations::GetInstance()->Get(Id);
	float offSet = 0;
	ULONGLONG chargingTimer = CGame::GetInstance()->GetTickCount() - charging_start;
	if (chargingTimer < KOOPA_TROOPA_CHARGING_TIME && chargingTimer > KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION) {
		ULONGLONG unit = KOOPA_TROOPA_CHARGING_TIME * (1.0f - KOOPA_TROOPA_CHARGING_TIME_PROPORTION) / KOOPA_TROOPA_SHAKING_FREQUENCY;
		int temp = (chargingTimer - KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION) / unit;
		offSet = (temp % 2 == 0)? KOOPA_TROOPA_SHAKING_INTENSITY : -KOOPA_TROOPA_SHAKING_INTENSITY;
	}
	if (CGame::GetInstance()->IsFrozen()) {
		aniToRender->Render1Frame(x + offSet, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
	}
	else aniToRender->Render(x + offSet, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
}
