#pragma once
#include "Spawner.h"
#include "Goomba.h"
class CGoombaSpawner : public CSpawner
{
	CGoomba* obj = NULL;
public:
	CGoombaSpawner(float x, float y, int direction) : CSpawner(x, y, direction){}	//direction:	0:towards	1:away	2: left	3:right
	void Spawn();
	void Update(DWORD dt);
};

