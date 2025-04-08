#include "MarioKeyEventHandler.h"

void CMarioKeyEventHandler::KeyState(BYTE* state)
{

}

void CMarioKeyEventHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = (CMario*)(CGameObjectsManager::GetInstance()->GetPlayer());
}

void CMarioKeyEventHandler::OnKeyUp(int KeyCode)
{
}
