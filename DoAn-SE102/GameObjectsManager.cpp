#include "GameObjectsManager.h"
#include "debug.h"
CGameObjectsManager* CGameObjectsManager::__instance = NULL;

CGameObjectsManager* CGameObjectsManager::GetInstance() {
	if (__instance == NULL) __instance = new CGameObjectsManager();
	return __instance;
}

void CGameObjectsManager::Update(DWORD dt) {
	int score; CGame::GetInstance()->GetScore(score);
	if (!CGame::GetInstance()->IsFrozen()) {
		for (auto i : staticObjects) i->Update(dt);
		for (auto i : movableObjects) i->Update(dt);
		for (auto i : coinEffects) i->Update(dt);
		for (auto i : scoreEffects) i->Update(dt);
		for (auto i : fireBalls) i->Update(dt);
		for (auto i : spawners) i->Update(dt);
	}
	player->Update(dt);
}
void CGameObjectsManager::Render() {
	
	for (auto i : staticObjects) i->Render();
	for (auto i : movableObjects) i->Render();
	for (auto i : coinEffects) i->Render();
	for (auto i : scoreEffects) i->Render();
	for (auto i : fireBalls) i->Render();
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

	for (auto i : fireBalls) delete i;
	fireBalls.clear();

	for (auto i : spawners) delete i;
	spawners.clear();

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

void CGameObjectsManager::CheckCollisionWith(LPGAMEOBJECT srcObj, DWORD dt, bool player, bool movableObjects, bool staticObjects, bool others, int filterBlock, int filterX, int filterY) {
	vector<LPGAMEOBJECT> temp;
	if (player) temp.push_back(this->player);
	if (movableObjects) {
		for (auto i : this->movableObjects) {
			if(i != srcObj) temp.push_back(i);
		}
	}
	if (staticObjects) {
		for (auto i : this->staticObjects) {
			if (i != srcObj) temp.push_back(i);
		}
	}
	if (others) {
		for (auto i : fireBalls) {
			if (i->IsEnabled() && i!=srcObj) temp.push_back(i);
		}
	}
	CCollision::GetInstance()->Process(srcObj, dt, &temp, filterBlock, filterX, filterY);
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

LPFIREBALL CGameObjectsManager::GetFireBall(float x, float y, float angle) {
	for (LPFIREBALL i : fireBalls) {
		if (!i->IsEnabled()) {
			i->SetPosition(x, y);
			i->SetAngle(angle);
			i->ReEnable(); return i;
		}
	}
	LPFIREBALL newBall = new CFireBall(x, y);
	newBall->SetAngle(angle);
	newBall->ReEnable(); fireBalls.push_back(newBall);
	return newBall;
}