#include "Mario.h"
#include <string>
#include "Utils.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "KoopaTroopa.h"

void CMario::Update(DWORD dt) {

	if (state == MarioState::DIE) {
		if (CGame::GetInstance()->GetTickCount() - death_start < MARIO_DEATH_TIME * 0.2f) {
			maxVx = 0;
			vx = 0;
			maxVy = -1.0f;
			vy = -0.4f;
			ay = MARIO_GRAVITY;
			ax = 0;
		}
		else {
			vy += ay * dt;
			y += vy * dt;
		}
		return;
	}

	if (GetTickCount64() - level_start < level_duration) return;
	else CGame::GetInstance()->UnFreezeGame();

	if (CGame::GetInstance()->IsFrozen()) return;

	if (level == MarioLevel::SMALL || state == MarioState::SIT) height = MARIO_SMALL_BBOX_HEIGHT;
	else height = MARIO_BIG_BBOX_HEIGHT;

	if (CGame::GetInstance()->GetTickCount() - lastJumpTime > jumpTime) ay = MARIO_GRAVITY;

	if (shell != NULL) {
		if (!shell->IsIdling()) {
			shell->ReleaseHeld();
			shell = NULL;
		}
	}

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

	//Cheking collision for Mairo's head
	head->x = x; head->y = y - height;
	head->vx = vx; head->vy = vy;
	head->ProcessCollision(dt);

	//Check collision
	isGrounded = false;			//Before checking for collision, Mario is considered not touching the ground
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 1, 1);

	//Update position for the shell being held
	AdjustShellPosition();
}
void CMario::Render() {
	if (state == MarioState::DIE) {
		if(aniToRender != NULL) aniToRender->Render(x, y - MARIO_SMALL_BBOX_HEIGHT * 0.5f);
		return;
	}
	if (GetTickCount64() - level_start < level_duration) {
		aniToRender->RenderByDuration(x, y - MARIO_SMALL_BBOX_HEIGHT * 0.5f, 0);
		return;
	}
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) flicker_time = 0;
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
	if(aniToRender != NULL) aniToRender->Render(x, y - MARIO_SMALL_BBOX_HEIGHT * 0.5f, flicker_time);
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
	if (state == MarioState::SIT) {
		if (nx == 1) aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_SIT_RIGHT);
		else aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_SIT_LEFT);
		return;
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
	if (state == MarioState::SIT) {
		if (nx == 1) aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_SIT_RIGHT);
		else aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_SIT_LEFT);
		return;
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
		death_start = CGame::GetInstance()->GetTickCount();
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
		if (nx == 1) ResetTurningTimer();
		nx = -1;
		maxVx = -MARIO_WALK_SPEED;
		ax = -MARIO_WALK_ACCEL_X;
		break;
	case MarioState::WALK_RIGHT:
		if (nx == -1) ResetTurningTimer();
		nx = 1;
		maxVx = MARIO_WALK_SPEED;
		ax = MARIO_WALK_ACCEL_X;
		break;
	case MarioState::RUN_LEFT:
		if(nx == 1) ResetTurningTimer();
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
		if(nx == -1) ResetTurningTimer();
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
		this->state = state;
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
	if (dynamic_cast<CLevelUpItem*>(e->src_obj)) {
		OnCollisionWidthPowerUpItem(e);
	}
	if (dynamic_cast<CEnemy*>(e->obj)) {
		OncollisionWithEnemy(e);
	}
}
void CMario::OncollisionWithEnemy(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CGoomba*>(e->obj)) {
		OnCollisionWithGoomba(e);
		return;
	}
	if (dynamic_cast<CKoopaTroopa*>(e->obj)) {
		OnCollisionWidthKoopaTroopa(e);
		return;
	}
	OnLevelDown();
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	if((dynamic_cast<CGoomba*>(e->obj)->IsDead())) return;
	if (e->ny < 0) {
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		e->obj->OnCollisionWith(e);
	}
	else {
		if (GetTickCount64() - untouchable_start < MARIO_UNTOUCHABLE_TIME) return;
		if((dynamic_cast<CGoomba*>(e->obj)->IsUntouchable())) return;
		OnLevelDown();
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e) {

}
void CMario::OnCollisionWidthPowerUpItem(LPCOLLISIONEVENT e) {
	((CLevelUpItem*)e->src_obj)->Delete();
	OnLevelUp();
}
void CMario::OnCollisionWidthKoopaTroopa(LPCOLLISIONEVENT e) {
	if ((dynamic_cast<CKoopaTroopa*>(e->obj)->IsDead())) return;
	if (e->ny < 0) {
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		dynamic_cast<CKoopaTroopa*>(e->obj)->OnCollisionWithMario(e);
	}
	else {
		if (GetTickCount64() - untouchable_start < MARIO_UNTOUCHABLE_TIME) return;
		if ((dynamic_cast<CKoopaTroopa*>(e->obj)->IsUntouchable())) return;
		if (dynamic_cast<CKoopaTroopa*>(e->obj)->IsIdling()) {
			if (isRunButtonPressed && shell == NULL) {
				shell = dynamic_cast<CKoopaTroopa*>(e->obj);
				shell->OnHeld();
			}
			dynamic_cast<CKoopaTroopa*>(e->obj)->OnCollisionWithMario(e);
			return;
		}
		OnLevelDown();
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width / 2;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT * 0.5f;
	top = bottom - height;
	right = left + width;
	
}

void CMario::OnLevelUp() {
	if (level == MarioLevel::RACCOON) return;
	level_start = GetTickCount64();
	if (level == MarioLevel::SMALL) {
		if (nx == 1)
			aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_LEVELUP_RIGHT);
		else aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_LEVELUP_LEFT);
		aniToRender->Reset();
		aniToRender->SetDuration(MARIO_LEVEL_LONG_TIME);
		level_duration = MARIO_LEVEL_LONG_TIME;
	}
	else {
		aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_LEVELUP);
		aniToRender->Reset();
		aniToRender->SetDuration(MARIO_LEVEL_SHORT_TIME);
		level_duration = MARIO_LEVEL_SHORT_TIME;
	}
	level = (MarioLevel)(level + 1);
	CGame::GetInstance()->FreezeGame();
}

void CMario::OnLevelDown() {
	if (GetTickCount64() - untouchable_start < MARIO_UNTOUCHABLE_TIME) return;
	if (level == MarioLevel::SMALL) {
		CGame::GetInstance()->FreezeGame();
		SetState(MarioState::DIE);
	}
	else {
		level_start = GetTickCount64();
		untouchable_start = GetTickCount64();
		flicker_time = MARIO_FLICKER_TIME;

		if (level == MarioLevel::BIG) {
			if(nx == 1)
				aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_LEVELDOWN_RIGHT);
			else aniToRender = CAnimations::GetInstance()->Get(MARIO_BIG_ANIMATION_LEVELDOWN_LEFT);
			aniToRender->Reset();
			aniToRender->SetDuration(MARIO_LEVEL_LONG_TIME);
			level_duration = MARIO_LEVEL_LONG_TIME;
		}
		else {
			aniToRender = CAnimations::GetInstance()->Get(MARIO_RACCOON_ANIMATION_LEVELDOWN);
			aniToRender->Reset();
			aniToRender->SetDuration(MARIO_LEVEL_SHORT_TIME);
			level_duration = MARIO_LEVEL_SHORT_TIME;
		}
		level = (MarioLevel)(level - 1);
		CGame::GetInstance()->FreezeGame();
	}
}

void CMario::OnReleaseRunButton() {
	if (shell != NULL) {
		shell->ReleaseHeld();
		shell = NULL;
	}
	isRunButtonPressed = false; 
}

void CMario::ResetTurningTimer() {
	auto game = CGame::GetInstance();
	ULONGLONG timer = game->GetTickCount() - turning_start;
	if (timer > MARIO_TURNING_TIME) turning_start = game->GetTickCount();
	else {
		turning_start = game->GetTickCount() - (MARIO_TURNING_TIME - timer);
	}
}

void CMario::AdjustShellPosition() {
	if (shell != NULL) {
		float tempX, tempY;
		ULONGLONG turningTimer = CGame::GetInstance()->GetTickCount() - turning_start;
		switch (level) {
		case MarioLevel::SMALL:
			tempY = y - MARIO_SHELL_POSITION_OFFSET_SMALL_Y;
			if (nx == 1) {
				if (turningTimer < MARIO_TURNING_TIME) {
					tempX = x - MARIO_SHELL_POSITION_OFFSET_SMALL_X + (1.0f * turningTimer / MARIO_TURNING_TIME) * MARIO_SHELL_POSITION_OFFSET_SMALL_X * 2;
				}
				else tempX = x + MARIO_SHELL_POSITION_OFFSET_SMALL_X;
			}
			else {
				if (turningTimer < MARIO_TURNING_TIME) {
					tempX = x + MARIO_SHELL_POSITION_OFFSET_SMALL_X - (1.0f * turningTimer / MARIO_TURNING_TIME) * MARIO_SHELL_POSITION_OFFSET_SMALL_X * 2;
				}
				else tempX = x - MARIO_SHELL_POSITION_OFFSET_SMALL_X;
			}
			break;
		case MarioLevel::BIG:
		case MarioLevel::RACCOON:
			tempY = y - MARIO_SHELL_POSITION_OFFSET_BIG_Y;
			if (nx == 1) {
				if (turningTimer < MARIO_TURNING_TIME) {
					tempX = x - MARIO_SHELL_POSITION_OFFSET_BIG_X + (1.0f * turningTimer / MARIO_TURNING_TIME) * MARIO_SHELL_POSITION_OFFSET_BIG_X * 2;
				}
				else tempX = x + MARIO_SHELL_POSITION_OFFSET_BIG_X;
			}
			else {
				if (turningTimer < MARIO_TURNING_TIME) {
					tempX = x + MARIO_SHELL_POSITION_OFFSET_BIG_X - (1.0f * turningTimer / MARIO_TURNING_TIME) * MARIO_SHELL_POSITION_OFFSET_BIG_X * 2;
				}
				else tempX = x - MARIO_SHELL_POSITION_OFFSET_BIG_X;
			}
			break;
		}
		shell->SetPosition(tempX, tempY);
	}
}