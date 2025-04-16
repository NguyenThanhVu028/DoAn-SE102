#include "QuestionBlock.h"
void CQuestionBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - QUESTIONBLOCK_WIDTH * 0.5f;
	top = y - QUESTIONBLOCK_HEIGHT * 0.5f;
	right = x + QUESTIONBLOCK_WIDTH * 0.5f;
	bottom = y + QUESTIONBLOCK_HEIGHT * 0.5f;
}
void CQuestionBlock::Update(DWORD dt) {

}
void CQuestionBlock::Render() {
	if (!isVisible) return;

	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - 8 || x > cX + screenWidth + 8 || y < cY - 8 || y > cY + screenHeight + 8) return;

	int aniId;
	if (isAvailable) aniId = QUESTIONBLOCK_ANIMATION_AVAILABLE;
	else aniId = QUESTIONBLOCK_ANIMATION_UNAVAILABLE;

	float tempX = x, tempY = y;
	LONGLONG bounce_timer = GetTickCount64() - bounce_time_start;
	if ( bounce_timer < QUESTIONBLOCK_BOUNCE_TIME) {
		if(bounce_timer < QUESTIONBLOCK_BOUNCE_TIME * 0.5f){
			tempY = y - ((bounce_timer / (QUESTIONBLOCK_BOUNCE_TIME * 0.5f)) * QUESTIONBLOCK_BOUNCE_DISTANCE);
		}
		else {
			tempY = y - ((1 - (bounce_timer - QUESTIONBLOCK_BOUNCE_TIME * 0.5f) / (QUESTIONBLOCK_BOUNCE_TIME * 0.5f)) * QUESTIONBLOCK_BOUNCE_DISTANCE);
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(tempX, tempY);
}
void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!IsInteractable()) return;
	if (dynamic_cast<CMario*>(e->src_obj)) {
		if (e->ny > 0) {
			bounce_time_start = GetTickCount64();
			//isAvailable = false;
			//CGameObjectsManager::GetInstance()->GetCoinEffect(x, y - 16);
		}
	}
}