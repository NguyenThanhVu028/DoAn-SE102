#include "GreenKoopaTroopa.h"
#include "GameObjectsManager.h"
#include "Mario.h"
#include "QuestionBlock.h"

void CGreenKoopaTroopa::Render() {
	if (!isEnabled || isKilled) return;
	CKoopaTroopa::Render();
	if (hasWing && state == KoopaTroopaState::OUTSIDE) {
		float tempX = x;
		tempX += (vx > 0) ? -GREEN_KOOPATROOPA_WING_POSITION_OFFSET_X : GREEN_KOOPATROOPA_WING_POSITION_OFFSET_X;
		int aniToRender = 0;
		if (vx > 0) aniToRender = GREEN_KOOPA_TROOPA_ANIMATION_WING_RIGHT;
		else aniToRender = GREEN_KOOPA_TROOPA_ANIMATION_WING_LEFT;
		if(CGame::GetInstance()->IsFrozen()) CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(tempX, y - GREEN_KOOPATROOPA_WING_POSITION_OFFSET_Y);
		else CAnimations::GetInstance()->Get(aniToRender)->Render(tempX, y - GREEN_KOOPATROOPA_WING_POSITION_OFFSET_Y);
	}
}

void CGreenKoopaTroopa::RealRender() {
	if (aniToRender == NULL) aniToRender = CAnimations::GetInstance()->Get(GREEN_KOOPA_TROOPA_ANIMATION_WALK_RIGHT);

	if (CGame::GetInstance()->IsFrozen()) {
		aniToRender->Render1Frame(x, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
		return;
	}

	int Id = GREEN_KOOPA_TROOPA_ANIMATION_WALK_RIGHT;
	switch (state) {
	case KoopaTroopaState::K_DIE:
	case KoopaTroopaState::K_DIE_KICKED:
		Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? GREEN_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		break;
	case KoopaTroopaState::OUTSIDE:
		Id = (vx > 0) ? GREEN_KOOPA_TROOPA_ANIMATION_WALK_RIGHT : GREEN_KOOPA_TROOPA_ANIMATION_WALK_LEFT;
		break;
	case KoopaTroopaState::SHELL_IDLE:
		if (CGame::GetInstance()->GetTickCount() - charging_start < KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION)
			Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? GREEN_KOOPA_TROOPA_ANIMATION_SHELL_IDLE : GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_IDLE;
		else if (CGame::GetInstance()->GetTickCount() - charging_start <= KOOPA_TROOPA_CHARGING_TIME)
			Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? GREEN_KOOPA_TROOPA_ANIMATION_SHELL_CHARGING : GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_CHARGING;
		break;
	case KoopaTroopaState::SHELL_MOVING:
		Id = (shellDirection == KoopaTroopaShellDirection::NORMAL) ? GREEN_KOOPA_TROOPA_ANIMATION_SHELL_MOVING : GREEN_KOOPA_TROOPA_ANIMATION_SHELL_UPSIDEDOWN_MOVING;
		break;
	}
	aniToRender = CAnimations::GetInstance()->Get(Id);
	float offSet = 0;
	ULONGLONG chargingTimer = CGame::GetInstance()->GetTickCount() - charging_start;
	if (chargingTimer < KOOPA_TROOPA_CHARGING_TIME && chargingTimer > KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION) {
		ULONGLONG unit = KOOPA_TROOPA_CHARGING_TIME * (1.0f - KOOPA_TROOPA_CHARGING_TIME_PROPORTION) / KOOPA_TROOPA_SHAKING_FREQUENCY;
		int temp = (chargingTimer - KOOPA_TROOPA_CHARGING_TIME * KOOPA_TROOPA_CHARGING_TIME_PROPORTION) / unit;
		offSet = (temp % 2 == 0) ? KOOPA_TROOPA_SHAKING_INTENSITY : -KOOPA_TROOPA_SHAKING_INTENSITY;
	}
	aniToRender->Render(x + offSet, y - (height - KOOPA_TROOPA_SHELL_HEIGHT) * 0.5f + 2);
}

void CGreenKoopaTroopa::Update(DWORD dt) {
	if (isKilled || !isEnabled) return;
	CKoopaTroopa::Update(dt);

	if (state == KoopaTroopaState::K_DIE || state == KoopaTroopaState::K_DIE_KICKED) return;
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1, 0);
}

void CGreenKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	CKoopaTroopa::OnCollisionWith(e);
	if (e->ny != 0 && e->obj->IsBlocking()) {
		if (e->ny < 0 && hasWing) vy = -GREEN_KOOPATROOPA_JUMP_SPEED;
		else vy = 0;
	}
}

void CGreenKoopaTroopa::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	if (hasWing) {
		hasWing = false;
		untouchable_start = CGame::GetInstance()->GetTickCount();
	}
	else CKoopaTroopa::OnCollisionWithMario(e);
}

void CGreenKoopaTroopa::SetEnable(bool t) {
	hasWing = hasWingOri;
	CKoopaTroopa::SetEnable(t);
}