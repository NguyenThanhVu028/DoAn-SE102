#include "Spawner.h"
#include "GameObjectsManager.h"

void CSpawner::Update(DWORD dt) {

	float cX, cY;
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	CGame::GetInstance()->GetCamPos(cX, cY);

	if (x > cX - DESPAWN_OFFSET * 0.5f && x < cX + screenWidth + DESPAWN_OFFSET * 0.5f && y > cY - DESPAWN_OFFSET * 0.5f && y < cY + screenHeight + DESPAWN_OFFSET * 0.5f) {
		if (playerOut) {
			Spawn();
		}
		playerOut = false;
	}
	else playerOut = true;

	//float pX, pY;
	//CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
	//if (isVertical) {
	//	if (pX >= lowTrespass && pX <= highTrespass) {

	//	}
	//	else playerOut = true;
	//}
	//else {
	//	if (pY >= lowTrespass && pY <= highTrespass) {
	//		if (playerOut) {
	//			Spawn();
	//		}
	//		playerOut = false;
	//	}
	//	else playerOut = true;
	//}
}