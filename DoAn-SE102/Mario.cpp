#include "Mario.h"
#include <string>
#include "Utils.h"

void CMario::Update(DWORD dt) {

	if (GetTickCount64() - lastJumpTime > MARIO_JUMP_TIME) ay = MARIO_GRAVITY;

	float prevVx = vx;
	vx += ax * dt;
	vy += ay * dt;

	DebugOutTitle(L"Velocity: %f %f %f", prevVx, vx, maxVx);

	if (maxVx != 0) {
		if (maxVx * vx > 0) {
			if (abs(vx) > abs(maxVx)) {
				if (abs(prevVx) < abs(maxVx)) vx = maxVx;
				else {
					vx = prevVx + ((maxVx > 0) ? -1 : 1) * MARIO_DECEL_X * 2 * dt;
					if (abs(vx) < abs(maxVx)) vx = maxVx;
				}
			}
		}
		else {
			vx = prevVx + ((maxVx > 0) ? 1 : -1) * MARIO_BRAKE_DECEL * dt;
		}
	}
	else {
		if (prevVx == 0 || prevVx * vx < 0) vx = 0;
	}
	if (vy < maxVy) vy = maxVy;
	
	//Some timers

	//Check collision
	CGameObjectsManager::GetInstance()->CheckCollision(this, dt);
	//OnNoCollision(dt);
}
void CMario::Render() {
	CAnimations::GetInstance()->Get(10001)->Render(x, y);
	if (state == MarioState::DIE) {

	}
	else if (isGrounded == false) {
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
	case MarioState::DIE:
		SetState(MarioState::DIE);
		break;
	case MarioState::JUMP:
		if (isGrounded == true) {
			vy = -MARIO_JUMP_SPEED/2;
			ay = -MARIO_JUMP_ACCEL;
			ax = 0;
			maxVy = -MARIO_JUMP_SPEED;
			lastJumpTime = GetTickCount64();
		}
		break;
	//case MarioState::JUMP_WALK_LEFT:
	//	if (isGrounded == true) {
	//		//vx = -MARIO_WALKING_SPEED;
	//		ax = 0;
	//		vy = -MARIO_JUMP_SPEED / 2;
	//		ay = -MARIO_JUMP_ACCEL;
	//		maxVy = -MARIO_JUMP_SPEED;
	//		lastJumpTime = GetTickCount64();
	//	}
	//	break;
	//case MarioState::JUMP_WALK_RIGHT:
	//	if (isGrounded == true) {
	//		//vx = MARIO_WALKING_SPEED;
	//		ax = 0;
	//		vy = -MARIO_JUMP_SPEED / 2;
	//		ay = -MARIO_JUMP_ACCEL;
	//		maxVy = -MARIO_JUMP_SPEED;
	//		lastJumpTime = GetTickCount64();
	//	}
	//	break;
	case MarioState::RELEASE_JUMP:
		if (vy < 0) {
			ay = MARIO_GRAVITY;
		}
		break;
	case MarioState::IDLE:
		if (isGrounded) {
			maxVx = 0;
			if (vx > 0) ax = -MARIO_DECEL_X;
			else ax = MARIO_DECEL_X;
		}
		break;
	case MarioState::WALK_LEFT:
		nx = -1;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_WALKING_ACCEL_X;
		break;
	case MarioState::WALK_RIGHT:
		nx = 1;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_WALKING_ACCEL_X;
		break;
	case MarioState::RUN_LEFT:
		nx = -1;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_RUNNING_ACCEL_X;
		break;
	case MarioState::RUN_RIGHT:
		nx = 1;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_RUNNING_ACCEL_X;
		break;
	case MarioState::SIT:
		break;
	}


}

void CMario::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	isGrounded = false;
}
void CMario::OnCollisionWith(LPCOLLISIONEVENT e) {
	
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0; ay = MARIO_GRAVITY;
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