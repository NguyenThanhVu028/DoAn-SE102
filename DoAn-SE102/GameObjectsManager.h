#pragma once
#include <Windows.h>
#include <vector>

#include "GameObject.h"
class CGameObjectsManager
{
	static CGameObjectsManager* __instance;

	//Player
	
	//Movable Objects (Enemies, items, ...)
	vector<LPGAMEOBJECT> movableObjects;
	
	//Static Objects (Blocks, platforms, ...)
	vector<LPGAMEOBJECT> staticObjects;

public:
	static CGameObjectsManager* GetInstance();
	void Update(DWORD dt);
	void Render();
	void Clear();
};

