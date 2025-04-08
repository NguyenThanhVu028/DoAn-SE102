#include "Mario.h"
#include <string>
#include "Utils.h"

void CMario::Update(DWORD dt) {
	vx += ax * dt;
	vy += ay * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	
	//Some timers

	//Check collision
	CGameObjectsManager::GetInstance()->CheckCollision(this, dt);
	//OnNoCollision(dt);

}
void CMario::Render() {
	CAnimations::GetInstance()->Get(10001)->Render(x, y);
	if (state == MarioState::DIE) {

	}
	else if (isGrounded = false) {
		if (vy < 0) {

		}
		else {

		}
	}
	else {
		if (level == MarioLevel::SMALL) {

		}
		else if (level == MarioLevel::BIG) {

		}
		else if (level == MarioLevel::FOX) {

		}
	}
}

void CMario::SetState(MarioState state) {
	if (this->state == MarioState::DIE) return;
	switch (state) {

	}
}

void CMario::OnNoCollision(DWORD dt) {
	DebugOutTitle(L"Error %f", vy);
	x += vx * dt;
	y += vy * dt;
	isGrounded = false;
}
void CMario::OnCollisionWith(LPCOLLISIONEVENT e) {
	
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0; 
		if (e->ny < 0) isGrounded = true;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = 0;
	}
	
	///Dynamic cast

}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {

}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e) {

}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - MARIO_SMALL_BBOX_WIDTH / 2;
	top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
	right = left + MARIO_SMALL_BBOX_WIDTH;
	bottom = top + MARIO_SMALL_BBOX_HEIGHT;
}