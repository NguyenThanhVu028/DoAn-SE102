#include "PlaySceneUI.h"
#include "Sprites.h"
#include "Game.h"
#include "debug.h"
void PlaySceneUI::Update(DWORD dt) {

}

void PlaySceneUI::Render() {
	//DebugOutTitle(L"width height %d %d", CGame::GetInstance()->GetBackBufferWidth(), CGame::GetInstance()->GetBackBufferHeight());
	float x = CGame::GetInstance()->GetBackBufferWidth() * 0.5f;
	float y = CGame::GetInstance()->GetBackBufferHeight() - UI_BACKGROUND_HEIGHT * 0.5f;
	CSprites::GetInstance()->Get(UI_SPRITE_BACKGROUND)->DrawOnScreen(x, y);
}