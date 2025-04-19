#pragma once
#include "Spawner.h"
#include "RedGoomba.h"
class CRedGoombaSpawner : public CSpawner
{
	CRedGoomba* obj = NULL;
public:
	CRedGoombaSpawner(float x, float y, int direction) : CSpawner(x, y, direction) {}	//direction:	0:towards	1:away	2: left	3:right
	void Spawn();
	void Update(DWORD dt);
};

