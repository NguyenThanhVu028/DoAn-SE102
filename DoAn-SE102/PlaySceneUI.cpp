 #include "PlaySceneUI.h"
#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Mario.h"
#include "GameObjectsManager.h"
void CPlaySceneUI::Update(DWORD dt) {
	secondsRemain = CGame::GetInstance()->GetSecondsRemain();
}

void CPlaySceneUI::Render() {
	//Background
	float x = CGame::GetInstance()->GetBackBufferWidth() * 0.5f;
	float y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT * 0.5f;
	CSprites::GetInstance()->Get(UI_SPRITE_BACKGROUND)->DrawOnScreen(x, y);

	//Timer
	x = UI_TIMER_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_TIMER_POSY;
	LONG sec = secondsRemain;
	for (int i = 2; i >= 0; i--) {
		int temp = sec % 10;
		sec /= 10;
		CSprites::GetInstance()->Get(UI_SPRITE_NUMBER_OFFSET + temp)->DrawOnScreen(x + UI_SPRITE_NUMBER_WIDTH * i + UI_SPRITE_NUMBER_WIDTH * 0.5f, y + UI_SPRITE_NUMBER_HEIGHT * 0.5f);
	}

	//Coins
	int coins = CGame::GetInstance()->GetCoin();
	x = UI_COIN_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_COIN_POSY;
	for (int i = 1; i >= 0; i--) {
		int temp = coins % 10;
		if (i == 0 && temp == 0) break;
		coins /= 10;
		CSprites::GetInstance()->Get(UI_SPRITE_NUMBER_OFFSET + temp)->DrawOnScreen(x + UI_SPRITE_NUMBER_WIDTH * i + UI_SPRITE_NUMBER_WIDTH * 0.5f, y + UI_SPRITE_NUMBER_HEIGHT * 0.5f);
	}
	
	//Score
	int scores = CGame::GetInstance()->GetScore();
	x = UI_SCORE_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_SCORE_POSY;
	for (int i = 6; i >= 0; i--) {
		int temp = scores % 10;
		scores /= 10;
		CSprites::GetInstance()->Get(UI_SPRITE_NUMBER_OFFSET + temp)->DrawOnScreen(x + UI_SPRITE_NUMBER_WIDTH * i + UI_SPRITE_NUMBER_WIDTH * 0.5f, y + UI_SPRITE_NUMBER_HEIGHT * 0.5f);
	}

	//Lives
	int lives = CGame::GetInstance()->GetLives();
	x = UI_LIVES_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_LIVES_POSY;
	for (int i = 1; i >= 0; i--) {
		int temp = lives % 10;
		if (i == 0 && temp == 0) break;
		lives /= 10;
		CSprites::GetInstance()->Get(UI_SPRITE_NUMBER_OFFSET + temp)->DrawOnScreen(x + UI_SPRITE_NUMBER_WIDTH * i + UI_SPRITE_NUMBER_WIDTH * 0.5f, y + UI_SPRITE_NUMBER_HEIGHT * 0.5f);
	}

	//Worlds
	x = UI_WORLD_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_WORLD_POSY;
	CSprites::GetInstance()->Get(UI_SPRITE_NUMBER_OFFSET + 1)->DrawOnScreen(x + UI_SPRITE_NUMBER_WIDTH * 0.5f, y + UI_SPRITE_NUMBER_HEIGHT * 0.5f);

	//PMeter
	float unit = MARIO_PMETER_MAX * 1.0f / 7;
	x = UI_PMETER_POSX;
	y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT + UI_PMETER_POSY;
	CMario* mario = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
	if (mario != NULL) {
		int count = (int)(mario->GetPMeter() / unit);
		for (int i = 0; i < count; i++) {
			if (i == 6) {
				DWORD flickering;
				if (mario->IsPMeterMax()) flickering = UI_PMETER_MAX_ANIMATION_FAST_FLICKERING;
				else flickering = UI_PMETER_MAX_ANIMATION_SLOW_FLICKERING;
				CAnimations::GetInstance()->Get(UI_ANIMATION_PMETER_MAX)->RenderOnScreen(x + UI_SPRITE_PMETER_ARROW_WIDTH * 6 + UI_SPRITE_PMETER_MAX_WIDTH * 0.5f, y + UI_SPRITE_PMETER_MAX_HEIGHT * 0.5f, 500);
			}
			else
				CSprites::GetInstance()->Get(UI_SPRITE_PMETER_ARROW)->DrawOnScreen(x + UI_SPRITE_PMETER_ARROW_WIDTH * i + UI_SPRITE_PMETER_ARROW_WIDTH * 0.5f, y + UI_SPRITE_PMETER_ARROW_HEIGHT * 0.5f);
		}
	}

	//Overlay
	if (CGame::GetInstance()->GetTickCount() - fade_start < UI_FADE_TIME) {
		darkness = (CGame::GetInstance()->GetTickCount() - fade_start) * 1.0f / UI_FADE_TIME;
	}
	if (CGame::GetInstance()->GetTickCount() - brighten_start < UI_FADE_TIME) {
		darkness = 1.0f - (CGame::GetInstance()->GetTickCount() - brighten_start) * 1.0f / UI_FADE_TIME;
	}
	//DebugOutTitle(L"alpha %f", alpha);
	float tempX = 0, tempY = 0;
	while (tempY <= CGame::GetInstance()->GetBackBufferHeight()) {
		if (tempX > CGame::GetInstance()->GetBackBufferWidth()) {
			tempX = 0; tempY += 16;
		}
		CSprites::GetInstance()->Get(UI_BLACK_OVERLAY)->DrawOnScreen(tempX, tempY, darkness);
		tempX += 16;
	}
}

void CPlaySceneUI::StartFading() {
	fade_start = CGame::GetInstance()->GetTickCount();
	brighten_start = CGame::GetInstance()->GetTickCount() - UI_FADE_TIME - 10;
}

void CPlaySceneUI::StartBrightening() {
	brighten_start = CGame::GetInstance()->GetTickCount();
	fade_start = CGame::GetInstance()->GetTickCount() - UI_FADE_TIME - 10;
}