#include "FireBall.h"
#include "Game.h"
#include "debug.h"
#include <algorithm>

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - FIREBALL_WIDTH * 0.5f;
	top = y - FIREBALL_HEIGHT * 0.5f;
	right = x + FIREBALL_WIDTH * 0.5f;
	bottom = y + FIREBALL_WIDTH * 0.5f;
}

void CFireBall::Update(DWORD dt) {
	if (!isEnabled) return;
	x += vx * dt;
	y += vy * dt;
	float cx, cy;
	int screenWidth, screenHeight;
	CGame::GetInstance()->GetCamPos(cx, cy);
	screenWidth = CGame::GetInstance()->GetBackBufferWidth();
	screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x > cx + screenWidth || x < cx || y > cy + screenHeight || y < cy ) isEnabled = false;
}

void  CFireBall::Render() {
	if (!isEnabled) return;
	int aniToRender;
	if (vx > 0) {
		aniToRender = FIREBALL_ANIMATION_RIGHT;
	}
	else {
		aniToRender = FIREBALL_ANIMATION_LEFT;
	}
	if (CGame::GetInstance()->IsFrozen())
		CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(x, y);
	else CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
}

void CFireBall::OnNoCollision(DWORD dt) {

}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e) {

}

void CFireBall::SetAngle(float angle) {
	this->angle = angle;
	vy = sin(angle * 3.14f/180) * FIREBALL_SPEED;
	vx = cos(angle * 3.14f/180) * FIREBALL_SPEED;
}