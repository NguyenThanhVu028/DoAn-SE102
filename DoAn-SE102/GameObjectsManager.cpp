#include "GameObjectsManager.h"
#include "debug.h"
CGameObjectsManager* CGameObjectsManager::__instance = NULL;

CGameObjectsManager* CGameObjectsManager::GetInstance() {
	if (__instance == NULL) __instance = new CGameObjectsManager();
	return __instance;
}

void CGameObjectsManager::Update(DWORD dt) {
	int score; CGame::GetInstance()->GetScore(score);
	for (auto i : staticObjects) i->Update(dt);
	for (auto i : movableObjects) i->Update(dt);
	for (auto i : coinEffects) i->Update(dt);
	for (auto i : scoreEffects) i->Update(dt);
	player->Update(dt);
}
void CGameObjectsManager::Render() {
	
	for (auto i : staticObjects) i->Render();
	for (auto i : movableObjects) i->Render();
	for (auto i : coinEffects) i->Render();
	for (auto i : scoreEffects) i->Render();
	player->Render();
}
void CGameObjectsManager::Clear() {
	for (auto i : staticObjects) delete i;
	staticObjects.clear();

	for (auto i : movableObjects) delete i;
	movableObjects.clear();

	for (auto i : coinEffects) delete i;
	coinEffects.clear();

	for (auto i : scoreEffects) delete i;
	scoreEffects.clear();

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

void CGameObjectsManager::CheckCollisionWith(bool player, bool movableObjects, bool staticObjects, LPGAMEOBJECT srcObj, DWORD dt) {
	vector<LPGAMEOBJECT> temp;
	if (player) temp.push_back(this->player);
	if (movableObjects) {
		for (auto i : this->movableObjects) temp.push_back(i);
	}
	if (staticObjects) {
		for (auto i : this->staticObjects) temp.push_back(i);
	}
	CCollision::GetInstance()->Process(srcObj, dt, &temp);
	//CCollision::GetInstance()->Process(srcObj, dt, &movableObjects);
}

bool CGameObjectsManager::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

LPEFFECT CGameObjectsManager::GetCoinEffect(float x, float y, int value) {
	for (CEffect* i : coinEffects) {
		if (!i->IsEnabled()) {
			i->SetPosition(x, y);
			i->ReEnable(); return i;
		}
	}
	CCoinEffect* newEffect = new CCoinEffect(x, y);
	coinEffects.push_back(newEffect);
	return newEffect;
}

LPEFFECT CGameObjectsManager::GetScoreEffect(float x, float y, int value) {
	for (CEffect* i : scoreEffects) {
		if (!i->IsEnabled()) {
			i->SetPosition(x, y);
			((CScoreEffect*)i)->SetValue(value);
			i->ReEnable(); return i;
		}
	}
	CScoreEffect* newEffect = new CScoreEffect(x, y);
	newEffect->SetValue(value);
	scoreEffects.push_back(newEffect);
	return newEffect;
}