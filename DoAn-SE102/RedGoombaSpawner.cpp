#include "RedGoombaSpawner.h"
#include "GameObjectsManager.h"

void CRedGoombaSpawner::Spawn() {
	float pX, pY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
	if (obj == NULL) {
		if (!hasSpawned) {
			int nx = 0;
			switch (direction) {
			case 0:
				nx = (pX < x) ? -1 : 1;
				break;
			case 1:
				nx = (pX < x) ? 1 : -1;
				break;
			case 2:
				nx = -1;
				break;
			case 3:
				nx = 1;
				break;
			}
			obj = new CRedGoomba(x, y, nx);
			CGameObjectsManager::GetInstance()->AddMovableObject(obj);
			hasSpawned = true;
		}
	}
	else {
		if (!obj->IsEnabled()) {
			int nx = 0;
			switch (direction) {
			case 0:
				nx = (pX < x) ? -1 : 1;
				break;
			case 1:
				nx = (pX < x) ? 1 : -1;
				break;
			case 2:
				nx = -1;
				break;
			case 3:
				nx = 1;
				break;
			}
			obj->SetPosition(x, y);
			obj->SetDirection(nx);
			obj->SetEnable(true);
		}
	}
}

void CRedGoombaSpawner::Update(DWORD dt) {
	if (obj != NULL) {
		if (obj->IsKilled()) {
			obj->Delete();
			obj = NULL;
		}
	}
	CSpawner::Update(dt);
}