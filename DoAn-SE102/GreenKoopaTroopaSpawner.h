#pragma once
#include "Spawner.h"
#include "GreenKoopaTroopa.h"
class CGreenKoopaTroopaSpawner : public CSpawner
{
	CGreenKoopaTroopa* obj = NULL;
	bool hasWing;
public:
	CGreenKoopaTroopaSpawner(float x, float y, int nx, bool hasWing) : CSpawner(x, y, nx) {
		this->hasWing = hasWing;
	}
	void Spawn();
	void Update(DWORD dt);
};

