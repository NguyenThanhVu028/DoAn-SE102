#include "GoombaSpawner.h"
#include "GameObjectsManager.h"

void CGoombaSpawner::Spawn() {
	float pX, pY;
	CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);
	if (obj == NULL) {
		if (!hasSpawned) {
			int nx = 0;
			if (pX < x) nx = (sameDirection)? - 1 : 1;
			else nx = (sameDirection)? 1 : -1;
			obj = new CGoomba(x, y, nx);
			CGameObjectsManager::GetInstance()->AddMovableObject(obj);
			hasSpawned = true;
		}
	}
	else {
		if (!obj->IsEnabled()) {
			int nx = 0;
			if (pX < x) nx = (sameDirection) ? -1 : 1;
			else nx = (sameDirection) ? 1 : -1;
			obj->SetPosition(x, y);
			obj->SetDirection(nx);
			obj->SetEnable(true);
		}
	}
}

void CGoombaSpawner::Update(DWORD dt) {
	if (obj != NULL) {
		if (obj->IsKilled()) {
			obj->Delete();
			obj = NULL;
		}
	}
	CSpawner::Update(dt);
}