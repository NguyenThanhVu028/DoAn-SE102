#pragma once
#include <Windows.h>
#include <vector>

#include "GameObject.h"
#include "Effect.h"
#include "CoinEffect.h"
#include "ScoreEffect.h"
#include "DebrisEffect.h"
#include "WhackEffect.h"
#include "SmokeEffect.h"
#include "FireBall.h"
#include "Spawner.h"
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

	vector<LPSPAWNER> spawners;

	vector<LPEFFECT> debrisEffects;

	vector<LPEFFECT> whackEffects;

	vector<LPEFFECT> smokeEffects;

public:
	CGameObjectsManager() {
		Clear();
	}
	static CGameObjectsManager* GetInstance();

	LPGAMEOBJECT GetPlayer() { return player; };
	void SetPlayer(LPGAMEOBJECT p) { player = p; }

	LPEFFECT GetCoinEffect(float x, float y, int value);
	LPEFFECT GetScoreEffect(float x, float y, int value);
	LPEFFECT GetDebrisEffect(float x, float y);
	LPEFFECT GetWhackEffect(float x, float y);
	LPEFFECT GetSmokeEffect(float x, float y);
	LPFIREBALL GetFireBall(float x, float y, float angle = 10);


	void Update(DWORD dt);
	void Render();
	void Clear();
	void PurgeDeletedObjects();
	void AddStaticObject(LPGAMEOBJECT p) { staticObjects.push_back(p); }
	void AddSpawner(LPSPAWNER e) { spawners.push_back(e); }
	vector<LPGAMEOBJECT> GetStaticObjects() { return staticObjects; }
	void AddMovableObject(LPGAMEOBJECT p) { movableObjects.push_back(p); }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void CheckCollisionWith(LPGAMEOBJECT srcObj, DWORD dt, bool player = false, bool movableObjects = false, bool staticObjects = false, bool others = true, int filterBlock = 1, int filterX = 1, int filterY = 1);
};

