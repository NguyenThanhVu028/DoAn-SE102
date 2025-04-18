#include "Mario.h"
#include <string>
#include "Utils.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Goomba.h"

void CMario::Update(DWORD dt) {
	//DebugOutTitle(L"state %d", state);

	if (CGame::GetInstance()->GetTickCount() - lastJumpTime > jumpTime) ay = MARIO_GRAVITY;

	float prevVx = vx;
	vx += ax * dt;
	vy += ay * dt;

	//Velocity correction
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
	if (maxFallSpeed != -1 && vy > maxFallSpeed) vy = maxFallSpeed;

	//Check collision
	isGrounded = false;			//Before checking for collision, Mario is considered not touching the ground
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1);

}
void CMario::Render() {
	if (state == MarioState::DIE) {
		if(aniToRender != NULL) aniToRender->Render(x, y - (height - MARIO_SMALL_BBOX_HEIGHT) * 0.5f);
	}
	else {
		switch (level) {
		case MarioLevel::SMALL:
			GetAnimationSMALL();
			break;
		case MarioLevel::BIG:
			GetAnimationBIG();
			break;
		case MarioLevel::RACCOON:
			GetAnimationRACCOON();
			break;
		}
		if(aniToRender != NULL) aniToRender->Render(x, y - (height - MARIO_SMALL_BBOX_HEIGHT) * 0.5f);
	}
}

void CMario::GetAnimationSMALL() {
	if (!isGrounded) {		//If Mario is falling
		if (nx == 1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) { 
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_JUMP_RIGHT); 
				return; 
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_RIGHT);
				return;
			}
		}
		else if (nx == -1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_JUMP_LEFT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_LEFT);
				return;
			}
		}
	}
	if (vx == 0) {					//If Mario is idling
		if (nx == 1) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_IDLE_RIGHT);
			return;
		}
		aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_IDLE_LEFT);
		return;
	}
	if (nx == 1) {
		if (vx < 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_BRAKE_RIGHT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_WALK_RIGHT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_RUN_RIGHT);
				return;
			}
			else { 
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_RUN_MAXSPEED_RIGHT);
				return; 
			}
		}
	}
	else {
		if (vx > 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_BRAKE_LEFT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_WALK_LEFT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_RUN_LEFT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_RUN_MAXSPEED_LEFT);
				return;
			}
		}
	}
}

void CMario::GetAnimationBIG() {
	aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_IDLE_RIGHT);
	if (!isGrounded) {
		if (nx == 1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) { 
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_JUMP_RIGHT); 
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_FALL_RIGHT);
				}
				return; 
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_JUMP_MAXSPEED_RIGHT);
				return;
			}
		}
		else if (nx == -1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_JUMP_LEFT);
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_FALL_LEFT);
				}
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_JUMP_MAXSPEED_LEFT);
				return;
			}
		}
	}
	if (vx == 0) {
		if (nx == 1) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_IDLE_RIGHT);
			return;
		}
		aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_IDLE_LEFT);
		return;
	}
	if (nx == 1) {
		if (vx < 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_BRAKE_RIGHT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_WALK_RIGHT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_RUN_RIGHT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_RUN_MAXSPEED_RIGHT);
				return;
			}
		}
	}
	else {
		if (vx > 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_BRAKE_LEFT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_WALK_LEFT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_RUN_LEFT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_RUN_MAXSPEED_LEFT);
				return;
			}
		}
	}
}

void CMario::GetAnimationRACCOON() {
	aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_IDLE_RIGHT);
	if (!isGrounded) {
		if (nx == 1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_JUMP_RIGHT);
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_FALL_RIGHT);
				}
				return;
			}
			else {
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_JUMP_MAXSPEED_RIGHT);
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_FALL_MAXSPEED_RIGHT);
				}
				return;
			}
		}
		else if (nx == -1) {
			if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_JUMP_LEFT);
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_FALL_LEFT);
				}
				return;
			}
			else {
				if (vy < 0) {																//Mario is jumping up
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_JUMP_MAXSPEED_LEFT);
				}
				else {																		//Mario is falling
					aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_FALL_MAXSPEED_LEFT);
				}
				return;
			}
		}
	}
	if (vx == 0) {
		if (nx == 1) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_IDLE_RIGHT);
			return;
		}
		aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_IDLE_LEFT);
		return;
	}
	if (nx == 1) {
		if (vx < 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_BRAKE_RIGHT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_WALK_RIGHT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_RUN_RIGHT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_RUN_MAXSPEED_RIGHT);
				return;
			}
		}
	}
	else {
		if (vx > 0) {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_BRAKE_LEFT);
			return;
		}
		else {
			if (abs(vx) <= abs(MARIO_WALK_SPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_WALK_LEFT);
				return;
			}
			else if (abs(vx) < abs(MARIO_RUN_MAXSPEED)) {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_RUN_LEFT);
				return;
			}
			else {
				aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_RUN_MAXSPEED_LEFT);
				return;
			}
		}
	}
}

void CMario::SetState(MarioState state) {
	if (this->state == MarioState::DIE) return;
	switch (state) {
	case MarioState::DIE:
		this->state = state;
		vx = 0;
		ax = 0;
		aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_DIE);
		break;
	case MarioState::JUMP:
		if (isGrounded == true) {
			//Adjust jump time based on player's speed
			if (abs(vx) < MARIO_WALK_SPEED * 0.3f) jumpTime = MARIO_JUMP_TIME;
			else if (abs(vx) <= MARIO_WALK_SPEED) jumpTime = MARIO_JUMP_WALK_TIME;
			else if (abs(vx) <= MARIO_RUN_SPEED) jumpTime = MARIO_JUMP_RUN_TIME;
			else if (abs(vx) <= MARIO_RUN_MAXSPEED) jumpTime = MARIO_JUMP_RUN_MAXSPEED_TIME;
			vy = -MARIO_JUMP_SPEED * 0.5f;
			ay = -MARIO_JUMP_ACCEL;
			//ax = 0;
			maxVy = -MARIO_JUMP_SPEED;
			lastJumpTime = CGame::GetInstance()->GetTickCount();
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
		else {
			if (vx > 0) ax = -MARIO_DECEL_X * 0.2f;
			else ax = MARIO_DECEL_X * 0.2f;
		}
		this->state = state;
		break;
	case MarioState::WALK_LEFT:
		nx = -1;
		maxVx = -MARIO_WALK_SPEED;
		ax = -MARIO_WALK_ACCEL_X;
		break;
	case MarioState::WALK_RIGHT:
		nx = 1;
		maxVx = MARIO_WALK_SPEED;
		ax = MARIO_WALK_ACCEL_X;
		break;
	case MarioState::RUN_LEFT:
		nx = -1;
		//if (!isGrounded) {
		//	if(vx > 0) ax = -MARIO_RUNNING_ACCEL_X;
		//}
		//else                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

		ax = -MARIO_RUN_ACCEL_X;
		if (isGrounded && vx < -MARIO_WALK_SPEED) {
			pMeter += CGame::GetInstance()->GetTickCount() - pMeterCheckpoint;
			if (pMeter > MARIO_PMETER_MAX) pMeter = MARIO_PMETER_MAX;
		}
		else {
			if (pMeter < MARIO_PMETER_MAX || vx > -MARIO_WALK_SPEED) pMeter -= (CGame::GetInstance()->GetTickCount() - pMeterCheckpoint) / 2;
			if (pMeter < 0) pMeter = 0;
		}
		pMeterCheckpoint = CGame::GetInstance()->GetTickCount();

		if (pMeter >= MARIO_PMETER_MAX) maxVx = -MARIO_RUN_MAXSPEED;
		else maxVx = -MARIO_RUN_SPEED;

		break;
	case MarioState::RUN_RIGHT:
		nx = 1;
		/*if (!isGrounded) {
			if(vx < 0) ax = MARIO_RUNNING_ACCEL_X;
		}
		else*/ 
		ax = MARIO_RUN_ACCEL_X;
		if (isGrounded && vx > MARIO_WALK_SPEED) {
			pMeter += CGame::GetInstance()->GetTickCount() - pMeterCheckpoint;
			if (pMeter > MARIO_PMETER_MAX) pMeter = MARIO_PMETER_MAX;
		}
		else {
			if (pMeter < MARIO_PMETER_MAX || vx < MARIO_WALK_SPEED) pMeter -= (CGame::GetInstance()->GetTickCount() - pMeterCheckpoint) / 2;
			if (pMeter < 0) pMeter = 0;
		}
		pMeterCheckpoint = CGame::GetInstance()->GetTickCount();

		if (pMeter >= MARIO_PMETER_MAX) maxVx = MARIO_RUN_MAXSPEED;
		else maxVx = MARIO_RUN_SPEED;

		break;
	case MarioState::SIT:
		if (level == MarioLevel::SMALL) return;
		break;
	case MarioState::NOT_RUN:
		pMeter -= (CGame::GetInstance()->GetTickCount() - pMeterCheckpoint) * 0.5;
		if (pMeter < 0) pMeter = 0;
		pMeterCheckpoint = CGame::GetInstance()->GetTickCount();
		break;
	}
}

void CMario::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	//isGrounded = false;
}
void CMario::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0; ay = MARIO_GRAVITY;
		if (e->ny < 0) {
			//isGrounded = true;
			float ml, mt, mr, mb;
			float objl, objt, objr , objb;
			GetBoundingBox(ml, mt, mr, mb);
			e->obj->GetBoundingBox(objl, objt, objr, objb);
			if (!(mr < objl|| ml > objr)) {
				isGrounded = true;
			}
		}
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = 0;
	}
	//Dynamic cast
	if (dynamic_cast<CQuestionBlock*>(e->obj)) {
		dynamic_cast<CQuestionBlock*>(e->obj)->OnCollisionWith(e);
	}
	if (dynamic_cast<CLevelUpItem*>(e->src_obj)) {
		OnCollisionWidthPowerUpItem(e);
	}
	if (dynamic_cast<CGoomba*>(e->obj)) {
		OnCollisionWithGoomba(e);
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	if((dynamic_cast<CGoomba*>(e->obj)->IsDead())) return;
	if (e->ny < 0) {
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		e->obj->OnCollisionWith(e);
		/*dynamic_cast<CGoomba*>(e->obj)->SetState(GoombaState::FLATTENED);*/
	}
	else {
		OnLevelDown();
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e) {

}
void CMario::OnCollisionWidthPowerUpItem(LPCOLLISIONEVENT e) {
	((CLevelUpItem*)e->src_obj)->Delete();
	OnLevelUp();
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width / 2;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT * 0.5f;
	top = bottom - height;
	right = left + width;
	
}

void CMario::OnLevelUp() {
	level = (MarioLevel)(level + 1);
	height = MARIO_BIG_BBOX_HEIGHT;
}

void CMario::OnLevelDown() {
	if (level == MarioLevel::SMALL) {

	}
	else {
		level = (MarioLevel)(level - 1);
		if (level == MarioLevel::SMALL) height = MARIO_SMALL_BBOX_HEIGHT;
	}
}