#pragma once
#include "Game.h"
class CSpawner
{
protected:
	float lowTrespass, highTrespass;
	bool isVertical;
	float x, y;
	bool sameDirection;

	bool playerOut;
	bool hasSpawned;
public:
	CSpawner(float lowTresPass, float highTresPass, bool isVertical, float x, float y, bool sameDirection) {
		this->lowTrespass = lowTresPass;
		this->highTrespass = highTresPass;
		this->isVertical = isVertical;
		this->x = x; this->y = y; this->sameDirection = sameDirection;
		playerOut = true;
		hasSpawned = false;
	}
	virtual void Update(DWORD dt);
	virtual void Spawn() = 0;
};

typedef CSpawner* LPSPAWNER;

