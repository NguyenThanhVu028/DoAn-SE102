#include "Mario.h"
#include <string>
#include "Utils.h"
#include "QuestionBlock.h"

void CMario::Update(DWORD dt) {
	int coin; CGame::GetInstance()->GetCoin(coin);

	if (GetTickCount64() - lastJumpTime > MARIO_JUMP_TIME) ay = MARIO_GRAVITY;

	float prevVx = vx;
	vx += ax * dt;
	vy += ay * dt;

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
	//(L"PMeter: %d %f", pMeter, vx);
	if (vy < maxVy) vy = maxVy;
	
	//Some timers

	//Check collision
	CGameObjectsManager::GetInstance()->CheckCollision(this, dt);

}
void CMario::Render() {
	//CAnimations::GetInstance()->Get(10001)->Render(x, y);
	if (state == MarioState::DIE) {
		CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_DIE)->Render(x, y);
	}
	else {
		int aniId;
		switch (level) {
		case MarioLevel::SMALL:
			aniId = GetAnimationSMALL();
			break;
		case MarioLevel::BIG:
			aniId = GetAnimationBIG();
			break;
		case MarioLevel::FOX:
			aniId = GetAnimationFOX();
			break;
		}
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	//else if (isGrounded == false) {
	//	if (vy < 0) {

	//	}
	//	else {

	//	}
	//}
	//else {
	//	if (level == MarioLevel::SMALL) {

	//	}
	//	else if (level == MarioLevel::BIG) {

	//	}
	//	else if (level == MarioLevel::FOX) {

	//	}
	//}
}

int CMario::GetAnimationSMALL() {
	if (isGrounded == false) {
		if (nx == 1) {
			if (abs(vx) < abs(MARIO_RUNNING_MAXSPEED)) return MARIO_SMALL_ANIMATION_JUMP_RIGHT;
			else return MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_RIGHT;
		}
		else if (nx == -1) {
			if (abs(vx) < abs(MARIO_RUNNING_MAXSPEED)) return MARIO_SMALL_ANIMATION_JUMP_LEFT;
			else return MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_LEFT;
		}
	//	//if (nx == 1 && abs(vx) < abs(MARIO_RUNNING_SPEED)) 
	//	//else if(nx == 1)
	}
	if (vx == 0) {
		if (nx == 1) return MARIO_SMALL_ANIMATION_IDLE_RIGHT;
		return MARIO_SMALL_ANIMATION_IDLE_LEFT;
	}
	if (nx == 1) {
		if(vx < 0) return MARIO_SMALL_ANIMATION_BRAKE_RIGHT;	
		else {
			if (abs(vx) <= abs(MARIO_WALKING_SPEED)) return MARIO_SMALL_ANIMATION_WALK_RIGHT;
			else if (abs(vx) < abs(MARIO_RUNNING_MAXSPEED)) return MARIO_SMALL_ANIMATION_RUN_RIGHT;
			else return MARIO_SMALL_ANIMATION_RUN_MAXSPEED_RIGHT;
		}
	}
	else {
		if (vx > 0) return MARIO_SMALL_ANIMATION_BRAKE_LEFT;	
		else {
			if (abs(vx) <= abs(MARIO_WALKING_SPEED)) return MARIO_SMALL_ANIMATION_WALK_LEFT;
			else if (abs(vx) < abs(MARIO_RUNNING_MAXSPEED)) return MARIO_SMALL_ANIMATION_RUN_LEFT;
			else return MARIO_SMALL_ANIMATION_RUN_MAXSPEED_LEFT;
		}
	}
	return MARIO_SMALL_ANIMATION_IDLE_RIGHT;	//Default animation
}

int CMario::GetAnimationBIG() {
	return MARIO_SMALL_ANIMATION_IDLE_RIGHT;
}

int CMario::GetAnimationFOX() {
	return MARIO_SMALL_ANIMATION_IDLE_RIGHT;
}

void CMario::SetState(MarioState state) {
	if (this->state == MarioState::DIE) return;
	switch (state) {
	case MarioState::DIE:
		this->state = state;
		vx = 0;
		ax = 0;
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
		//if (!isGrounded) {
		//	if(vx > 0) ax = -MARIO_RUNNING_ACCEL_X;
		//}
		//else                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
		ax = -MARIO_RUNNING_ACCEL_X;
		if (isGrounded && vx < -MARIO_WALKING_SPEED) {
			pMeter += GetTickCount64() - pMeterCheckpoint;
			if (pMeter > MARIO_PMETER_MAX) pMeter = MARIO_PMETER_MAX;
		}
		else {
			if (pMeter < MARIO_PMETER_MAX || vx > -MARIO_WALKING_SPEED) pMeter -= (GetTickCount64() - pMeterCheckpoint) * 0.5;
			if (pMeter < 0) pMeter = 0;
		}
		pMeterCheckpoint = GetTickCount64();

		if (pMeter >= MARIO_PMETER_MAX) maxVx = -MARIO_RUNNING_MAXSPEED;
		else maxVx = -MARIO_RUNNING_SPEED;

		break;
	case MarioState::RUN_RIGHT:
		nx = 1;
		/*if (!isGrounded) {
			if(vx < 0) ax = MARIO_RUNNING_ACCEL_X;
		}
		else*/ 
		ax = MARIO_RUNNING_ACCEL_X;
		if (isGrounded && vx > MARIO_WALKING_SPEED) {
			pMeter += GetTickCount64() - pMeterCheckpoint;
			if (pMeter > MARIO_PMETER_MAX) pMeter = MARIO_PMETER_MAX;
		}
		else {
			if (pMeter < MARIO_PMETER_MAX || vx < MARIO_WALKING_SPEED) pMeter -= (GetTickCount64() - pMeterCheckpoint) * 0.5;
			if (pMeter < 0) pMeter = 0;
		}
		pMeterCheckpoint = GetTickCount64();

		if (pMeter >= MARIO_PMETER_MAX) maxVx = MARIO_RUNNING_MAXSPEED;
		else maxVx = MARIO_RUNNING_SPEED;

		break;
	case MarioState::SIT:
		if (level == MarioLevel::SMALL) return;
		break;
	case MarioState::NOT_RUN:
		pMeter -= (GetTickCount64() - pMeterCheckpoint) * 0.5;
		if (pMeter < 0) pMeter = 0;
		pMeterCheckpoint = GetTickCount64();
		break;
	}
}

void CMario::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	isGrounded = false;
}
void CMario::OnCollisionWith(LPCOLLISIONEVENT e) {
	//DebugOutTitle(L"Collided %d", GetTickCount64());
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0; ay = MARIO_GRAVITY;
		if (e->ny < 0) isGrounded = true;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = 0;
	}
	
	///Dynamic cast
	if (dynamic_cast<CQuestionBlock*>(e->obj)) {
		dynamic_cast<CQuestionBlock*>(e->obj)->OnCollisionWith(e);
	}
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