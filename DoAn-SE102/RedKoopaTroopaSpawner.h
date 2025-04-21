#pragma once
#include "Spawner.h"
#include "RedKoopaTroopa.h"
class CRedKoopaTroopaSpawner : public CSpawner
{
	CRedKoopaTroopa* obj = NULL;
public:
	CRedKoopaTroopaSpawner(float x, float y, int nx) : CSpawner(x, y, nx) {}
	void Spawn();
	void Update(DWORD dt);
};

