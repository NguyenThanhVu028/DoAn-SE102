#include "GameObjectsManager.h"
CGameObjectsManager* CGameObjectsManager::__instance = NULL;

CGameObjectsManager* CGameObjectsManager::GetInstance() {
	if (__instance == NULL) __instance = new CGameObjectsManager();
	return __instance;
}

void CGameObjectsManager::Update(DWORD dt) {
	player->Update(dt);
	for (auto i : staticObjects) i->Update(dt);
	for (auto i : movableObjects) i->Update(dt);
}
void CGameObjectsManager::Render() {
	player->Render();
	for (auto i : staticObjects) i->Render();
	for (auto i : movableObjects) i->Render();
}
void CGameObjectsManager::Clear() {
	for (auto i : staticObjects) delete i;
	staticObjects.clear();

	for (auto i : movableObjects) delete i;
	movableObjects.clear();

	delete player;
	player = NULL;
}
void CGameObjectsManager::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = staticObjects.begin(); it != staticObjects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	staticObjects.erase(
		std::remove_if(staticObjects.begin(), staticObjects.end(), CGameObjectsManager::IsGameObjectDeleted),
		staticObjects.end());

	for (it = movableObjects.begin(); it != movableObjects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	movableObjects.erase(
		std::remove_if(movableObjects.begin(), movableObjects.end(), CGameObjectsManager::IsGameObjectDeleted),
		movableObjects.end());

	//// NOTE: remove_if will swap all deleted items to the end of the vector
	//// then simply trim the vector, this is much more efficient than deleting individual items
	//objects.erase(
	//	std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
	//	objects.end());
}

void CGameObjectsManager::CheckCollision(LPGAMEOBJECT srcObj, DWORD dt) {
	vector<LPGAMEOBJECT> temp;
	for (auto i : staticObjects) temp.push_back(i);
	for (auto i : movableObjects) temp.push_back(i);
	CCollision::GetInstance()->Process(srcObj, dt, &temp);
	//CCollision::GetInstance()->Process(srcObj, dt, &movableObjects);
}

bool CGameObjectsManager::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }