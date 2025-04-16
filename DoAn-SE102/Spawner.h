#pragma once
#include "Game.h"
class CSpawner
{
protected:
	float lowTrespass, highTrespass;
	bool isVertical;
	float x, y;
	int direction;

	bool playerOut;
	bool hasSpawned;
public:
	CSpawner(float x, float y, int direction) {
		this->x = x; this->y = y; this->direction = direction;
		playerOut = true;
		hasSpawned = false;
	}
	virtual void Update(DWORD dt);
	virtual void Spawn() = 0;
};

typedef CSpawner* LPSPAWNER;

