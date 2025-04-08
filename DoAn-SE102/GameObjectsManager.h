#pragma once
#include <Windows.h>
#include <vector>

#include "GameObject.h"
class CGameObjectsManager
{
	static CGameObjectsManager* __instance;

	//Player
	LPGAMEOBJECT player;
	
	//Movable Objects (Enemies, items, ...)
	vector<LPGAMEOBJECT> movableObjects;
	
	//Static Objects (Blocks, platforms, ...)
	vector<LPGAMEOBJECT> staticObjects;

public:
	CGameObjectsManager() {
		Clear();
	}
	static CGameObjectsManager* GetInstance();
	LPGAMEOBJECT GetPlayer() { return player; };
	void SetPlayer(LPGAMEOBJECT p) { player = p; }
	void Update(DWORD dt);
	void Render();
	void Clear();
	void PurgeDeletedObjects();
	void AddStaticObject(LPGAMEOBJECT p) { staticObjects.push_back(p); }
	vector<LPGAMEOBJECT> GetStaticObjects() { return staticObjects; }
	void AddMovableObject(LPGAMEOBJECT p) { movableObjects.push_back(p); }
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void CheckCollision(LPGAMEOBJECT srcObj, DWORD dt);
};

