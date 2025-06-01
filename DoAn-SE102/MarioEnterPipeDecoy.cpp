#include "MarioEnterPipeDecoy.h"
#include "EnterablePipe.h"

void CMarioEnterPipeDecoy::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	float width, height;
	CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
	if (mario != NULL) {
		if (mario->GetLevel() == MarioLevel::SMALL) {
			width = MARIO_SMALL_BBOX_WIDTH; height = MARIO_SMALL_BBOX_HEIGHT;
		}
		else width = MARIO_BIG_BBOX_WIDTH; height = MARIO_BIG_BBOX_HEIGHT;
	}
	left = x - width / 2;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT * 0.5f;
	top = bottom - height;
	right = left + width;
}

void CMarioEnterPipeDecoy::Render() {
	int aniToRender = MARIO_SMALL_ANIMATION_ENTER_PIPE;
	CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
	if (mario->GetLevel() == MarioLevel::BIG) aniToRender = MARIO_BIG_ANIMATION_ENTER_PIPE;
	else if(mario->GetLevel() == MarioLevel::RACCOON) aniToRender = MARIO_RACCOON_ANIMATION_ENTER_PIPE;
	CAnimations::GetInstance()->Get(aniToRender)->Render(x, y - MARIO_SMALL_BBOX_HEIGHT * 0.5f);
}

void CMarioEnterPipeDecoy::Update(DWORD dt) {
	y += enterVelocity * dt;
	isOverlapPipe = false;
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 0, 1, 0);
	if (!isOverlapPipe && (CGame::GetInstance()->GetTickCount() - enter_start > MIN_ENTER_TIME)) {
		Delete();
		CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
		mario->UnHide();
		mario->SetState(MarioState::IDLE);
		mario->SetPosition(x, y);
		mario->SetSpeed(0, 0);
	}
}

void CMarioEnterPipeDecoy::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CEnterablePipe*>(e->obj)) isOverlapPipe = true;
}