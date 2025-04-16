#include "MarioKeyEventHandler.h"
#include "Game.h"

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
		//float vx, vy;
		//mario->GetSpeed(vx, vy);
		//if (vx > 0) {
		//	mario->SetState(MarioState::JUMP_WALK_RIGHT);
		//}
		//else if (vx < 0) {
		//	mario->SetState(MarioState::JUMP_WALK_LEFT);
		//}
		//else 
		mario->SetState(MarioState::JUMP);
	}
}

void CMarioKeyEventHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = (CMario*)(CGameObjectsManager::GetInstance()->GetPlayer());
	switch (KeyCode) {
	case DIK_S:
		mario->SetState(MarioState::RELEASE_JUMP);
	}
}
