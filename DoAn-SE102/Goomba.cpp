#include "Goomba.h"
#include "Game.h"
#include "GameObjectsManager.h"

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - GOOMBA_WIDTH * 0.5f;
	top = y - GOOMBA_HEIGHT * 0.5f;
	right = x + GOOMBA_WIDTH * 0.5f;
	bottom = y + GOOMBA_HEIGHT * 0.5f;
}

void CGoomba::Render() {
	//Check camera view
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - GOOMBA_WIDTH * 0.5f || x > cX + screenWidth + GOOMBA_WIDTH * 0.5f) return;
	if (y < cY - GOOMBA_HEIGHT * 0.5f || y > cY + screenHeight + GOOMBA_HEIGHT * 0.5f) { isDeleted = true; return; }

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
	CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
}

void CGoomba::Update(DWORD dt) {
	if (GetTickCount64() - dead_start > GOOMBA_DEAD_TIME && state == GoombaState::FLATTENED) {
		this->isDeleted = true; return;
	}
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
}

void CGoomba::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

bool CGoomba::IsDead() {
	return (state == GoombaState::FLATTENED || state == GoombaState::UPSIDE_DOWN);
}

void CGoomba::SetState(GoombaState state, int nx) {
	this->state = state;
	switch (state) {
	case GoombaState::ALIVE:
		break;
	case GoombaState::FLATTENED:
		vx = 0;
		dead_start = GetTickCount64();
		break;
	case GoombaState::UPSIDE_DOWN:
		vx = (nx == -1) ? GOOMBA_MOVING_SPEED * 2 : -GOOMBA_MOVING_SPEED * 2;
		vy = -GOOMBA_JUMP_DEFLECT_SPEED;
		break;
	}
}