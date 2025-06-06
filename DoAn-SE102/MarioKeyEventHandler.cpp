#include "MarioKeyEventHandler.h"
#include "Game.h"
#include "UIManager.h"

void CMarioKeyEventHandler::KeyState(BYTE* state)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)(CGameObjectsManager::GetInstance()->GetPlayer());
	mario->SetState(MarioState::IDLE);
	if (game->IsKeyDown(DIK_LEFTARROW)) {
		if (game->IsKeyDown(DIK_A)) {
			mario->SetState(MarioState::RUN_LEFT);
		}
		else {
			mario->SetState(MarioState::WALK_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_RIGHTARROW)) {
		if (game->IsKeyDown(DIK_A)) {
			mario->SetState(MarioState::RUN_RIGHT);
		}
		else {
			mario->SetState(MarioState::WALK_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_DOWNARROW)) {
		mario->SetState(MarioState::SIT);
		mario->EnterPipe(1);
	}
	else if (game->IsKeyDown(DIK_UPARROW)) {
		mario->EnterPipe(0);
	}
	else mario->SetState(MarioState::IDLE);

	if (!(game->IsKeyDown(DIK_LEFTARROW) && game->IsKeyDown(DIK_A)) && !(game->IsKeyDown(DIK_RIGHTARROW) && game->IsKeyDown(DIK_A))) mario->SetState(MarioState::NOT_RUN);

}

void CMarioKeyEventHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = (CMario*)(CGameObjectsManager::GetInstance()->GetPlayer());
	switch (KeyCode) {
	case DIK_1:
		mario->SetState(MarioState::DIE);
		break;
	case DIK_S:
		mario->SetState(MarioState::JUMP);
		break;
	case DIK_P:
		mario->SetLevel(MarioLevel::RACCOON);
		break;
	case DIK_A:
		mario->OnPressRunButton();
		mario->SetState(MarioState::SPIN);
		break;
	case DIK_N:
		CGame::GetInstance()->InitiateSwitchScene(1);
		//CUIManager::GetInstance()->StartFading();
		break;
	case DIK_M:
		CUIManager::GetInstance()->StartEndGameSequence();
		break;
	}
}

void CMarioKeyEventHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = (CMario*)(CGameObjectsManager::GetInstance()->GetPlayer());
	switch (KeyCode) {
	case DIK_S:
		mario->SetState(MarioState::RELEASE_JUMP);
		break;
	case DIK_P:
		CGame::GetInstance()->UnFreezeGame();
		break;
	case DIK_A:
		mario->OnReleaseRunButton();
		break;
	}
}
