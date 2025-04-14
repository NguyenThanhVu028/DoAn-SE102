#pragma once
#include "Spawner.h"
#include "Goomba.h"
class CGoombaSpawner : public CSpawner
{
	CGoomba* obj = NULL;
public:
	CGoombaSpawner(float lowTresPass, float highTresPass, bool isVertical, float x, float y, bool sameDirection) : CSpawner(lowTresPass, highTresPass, isVertical, x, y, sameDirection){}
	void Spawn();
	void Update(DWORD dt);
};

