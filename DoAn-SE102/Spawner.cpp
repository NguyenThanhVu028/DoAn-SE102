#include "Spawner.h"
#include "GameObjectsManager.h"

void CSpawner::Update(DWORD dt) {
	float pX, pY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
	if (isVertical) {
		if (pX >= lowTrespass && pX <= highTrespass) {
			if (playerOut) {
				Spawn();
			}
			playerOut = false;
		}
		else playerOut = true;
	}
	else {
		if (pY >= lowTrespass && pY <= highTrespass) {
			if (playerOut) {
				Spawn();
			}
			playerOut = false;
		}
		else playerOut = true;
	}
}