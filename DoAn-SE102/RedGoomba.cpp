#include "RedGoomba.h"
#include "Game.h"
#include "debug.h"
#include "Mario.h"
#include "Brick.h"
#include "Coin.h"
#include "QuestionBlock.h"

void CRedGoomba::Render() {
	if (!isEnabled || isKilled) return;
	//Check camera view
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - GOOMBA_WIDTH * 0.5f - DESPAWN_OFFSET || x > cX + screenWidth + GOOMBA_WIDTH * 0.5f + DESPAWN_OFFSET) { 
		if (state == GoombaState::UPSIDE_DOWN) isKilled = true;
		else isEnabled = false;
		return;
	}
	if (y < cY - GOOMBA_HEIGHT * 0.5f - DESPAWN_OFFSET || y > cY + screenHeight + GOOMBA_HEIGHT * 0.5f + DESPAWN_OFFSET) { 
		if (state == GoombaState::UPSIDE_DOWN) isKilled = true;
		else isEnabled = false;
		return;
	}

	//Get animation Id
	int wingAniToRender;
	if (hasWings) {
		if (isCharging) wingAniToRender = RED_GOOMBA_WINGS_ANIMATION_FLAPPING;
		else wingAniToRender = RED_GOOMBA_WINGS_ANIMATION_CLOSED;
	}

	int aniToRender = RED_GOOMBA_ANIMATION_WALK;
	switch (state) {
	case GoombaState::ALIVE:
		aniToRender = RED_GOOMBA_ANIMATION_WALK;
		break;
	case GoombaState::FLATTENED:
		aniToRender = RED_GOOMBA_ANIMATION_FLATENNED;
		break;
	case GoombaState::UPSIDE_DOWN:
		aniToRender = RED_GOOMBA_ANIMATION_UPSIDE_DOWN;
		break;
	}
	if (CGame::GetInstance()->IsFrozen()) {
		if(hasWings) CAnimations::GetInstance()->Get(wingAniToRender)->Render1Frame(x, y);
		CAnimations::GetInstance()->Get(aniToRender)->Render1Frame(x, y);
	}
		
	else {
		if(hasWings) CAnimations::GetInstance()->Get(wingAniToRender)->Render(x, y);
		CAnimations::GetInstance()->Get(aniToRender)->Render(x, y);
	}

}

void CRedGoomba::Update(DWORD dt) {
	CGoomba::Update(dt);
	if (state == GoombaState::UPSIDE_DOWN) hasWings = false;
	if (vy == 0 && !IsDead()) vx = (nx == 1) ? GOOMBA_MOVE_SPEED : -GOOMBA_MOVE_SPEED;
	if (CGame::GetInstance()->GetTickCount() - jump_timer > RED_GOOMBA_CYCLE && hasWings) {
		if (vy == 0) {
			vy = RED_GOOMBA_LONG_JUMP_SPEED;
			jump_timer = CGame::GetInstance()->GetTickCount();
			isCharging = false;

			float pX, pY;
			CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
			if (pX < x) nx = -1;
			else nx = 1;
		}
		return;
	}
	if (jump_timer != -1 && (CGame::GetInstance()->GetTickCount() - jump_timer > RED_GOOMBA_CYCLE * 0.5f) && hasWings) {
		if (vy == 0) vy = RED_GOOMBA_SHORT_JUMP_SPEED;
		isCharging = true;
	}
}

void CRedGoomba::SetEnable(bool t) {
	if (t == true) {
		hasWings = true;
	}
	jump_timer = CGame::GetInstance()->GetTickCount();
	CGoomba::SetEnable(t);
}


void CRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = 0;
	}
	if (e->nx != 0 && e->obj->IsBlocking()) {
		if (e->nx > 0) nx = 1;
		else nx = -1;
		//vx = -vx;
	}
	if (dynamic_cast<CMario*>(e->src_obj)) {
		OnCollisionWithMario(e);
	}
	if (dynamic_cast<CBrick*>(e->obj)) {
		if (dynamic_cast<CBrick*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
	if (dynamic_cast<CCoin*>(e->obj)) {
		if (dynamic_cast<CCoin*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
	if (dynamic_cast<CQuestionBlock*>(e->obj)) {
		if (dynamic_cast<CQuestionBlock*>(e->obj)->IsBouncing()) CMovableGameObject::OnCollisionWithBouncingBlock(e);
	}
}

void CRedGoomba::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	if (IsDead()) return;
	if (e->ny < 0) {
		if (hasWings) {
			hasWings = false;
			vy = 0;
			untouchable_start = CGame::GetInstance()->GetTickCount();
		}
		else {
			SetState(GoombaState::FLATTENED);
		}
	}
}

bool CRedGoomba::IsUntouchable() { return CGame::GetInstance()->GetTickCount() - untouchable_start < RED_GOOMBA_UNTOUCHABLE_TIME; }