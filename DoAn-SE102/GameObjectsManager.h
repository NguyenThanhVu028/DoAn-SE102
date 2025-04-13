#pragma once
#include <Windows.h>
#include <vector>

#include "GameObject.h"
#include "Effect.h"
#include "CoinEffect.h"
#include "ScoreEffect.h"
#include "FireBall.h"
class CGameObjectsManager
{
	static CGameObjectsManager* __instance;

	//Player
	LPGAMEOBJECT player;
	
	//Movable Objects (Enemies, items, ...)
	vector<LPGAMEOBJECT> movableObjects;
	
	//Static Objects (Blocks, platforms, ...)
	vector<LPGAMEOBJECT> staticObjects;

	//Effects
	vector<LPEFFECT> coinEffects;

	vector<LPEFFECT> scoreEffects;

	vector<LPFIREBALL> fireBalls;

public:
	CGameObjectsManager() {
		Clear();
	}
	static CGameObjectsManager* GetInstance();

	LPGAMEOBJECT GetPlayer() { return player; };
	void SetPlayer(LPGAMEOBJECT p) { player = p; }

	LPEFFECT GetCoinEffect(float x, float y, int value);
	LPEFFECT GetScoreEffect(float x, float y, int value);
	LPFIREBALL GetFireBall(float x, float y, float angle = 10);


	void Update(DWORD dt);
	void Render();
	void Clear();
	void PurgeDeletedObjects();
	void AddStaticObject(LPGAMEOBJECT p) { staticObjects.push_back(p); }
	vector<LPGAMEOBJECT> GetStaticObjects() { return staticObjects; }
	void AddMovableObject(LPGAMEOBJECT p) { movableObjects.push_back(p); }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void CheckCollisionWith(LPGAMEOBJECT srcObj, DWORD dt, bool player, bool movableObjects, bool staticObjects);
};

