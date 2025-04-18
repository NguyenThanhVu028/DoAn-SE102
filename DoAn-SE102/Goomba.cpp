#include "Goomba.h"
#include "Game.h"
#include "GameObjectsManager.h"
#include "debug.h"
#include "Mario.h"

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - GOOMBA_WIDTH * 0.5f;
	top = y - GOOMBA_HEIGHT * 0.5f;
	right = left + GOOMBA_WIDTH;
	bottom = top + GOOMBA_HEIGHT - 1;
}

void CGoomba::Render() {
	if (!isEnabled || isKilled) return;
	//Check camera view
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - GOOMBA_WIDTH * 0.5f - DESPAWN_OFFSET || x > cX + screenWidth + GOOMBA_WIDTH * 0.5f + DESPAWN_OFFSET) { isEnabled = false; return; }
	if (y < cY - GOOMBA_HEIGHT * 0.5f - DESPAWN_OFFSET || y > cY + screenHeight + GOOMBA_HEIGHT * 0.5f + DESPAWN_OFFSET) { isEnabled = false; return; }

	//Get animation Id
	int aniToRender = GOOMBA_ANIMATION_WALKING;
	switch (state) {
	case GoombaState::ALIVE:
		aniToRender = GOOMBA_ANIMATION_WALKING;
		break;
	case GoombaState::FLATTENED:
		aniToRender = GOOMBA_ANIMATION_FLATTENED;
		break;
	case GoombaState::UPSIDE_DOWN:
		aniToRender = GOOMBA_ANIMATION_UPSIDE_DOWN;
		break;
	}
	if(CGame::GetInstance()->IsFrozen())
		CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(x, y);
	else CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
}

void CGoomba::Update(DWORD dt) {
	if (isKilled) return;
	if (CGame::GetInstance()->GetTickCount() - dead_start > GOOMBA_DEAD_TIME && state == GoombaState::FLATTENED) {
		this->isKilled = true; return;
	}
	if (!isEnabled) return;
	vy += ay * dt;
	if (state != GoombaState::UPSIDE_DOWN) CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 0, 1);
	else CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 0, 0);
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	}
	if (dynamic_cast<CMario*>(e->src_obj)) {
		OnCollisionWithMario(e);
	}
}

void CGoomba::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	if (IsDead()) return;
	if (e->ny < 0) SetState(GoombaState::FLATTENED);
}

void CGoomba::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

bool CGoomba::IsDead() {
	return (state == GoombaState::FLATTENED || state == GoombaState::UPSIDE_DOWN || !isEnabled);
}

void CGoomba::SetState(GoombaState state, int nx) {
	this->state = state;
	switch (state) {
	case GoombaState::ALIVE:
		break;
	case GoombaState::FLATTENED:
		vx = 0;
		dead_start = CGame::GetInstance()->CGame::GetInstance()->GetTickCount();
		break;
	case GoombaState::UPSIDE_DOWN:
		vx = (nx == -1) ? GOOMBA_MOVING_SPEED * 2 : -GOOMBA_MOVING_SPEED * 2;
		vy = -GOOMBA_JUMP_DEFLECT_SPEED;
		break;
	}
}

void CGoomba::SetDirection(int nx) {
	CMovableGameObject::SetDirection(nx);
	if (nx == 1) vx = GOOMBA_MOVING_SPEED;
	else vx = -GOOMBA_MOVING_SPEED;
}