#pragma once

#include "Sprite.h"

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
	float offSetX, offSetY;

public:
	CAnimationFrame(LPSPRITE sprite, int time, float offSetX, float offSetY) { this->sprite = sprite; this->time = time; this->offSetX = offSetX; this->offSetY = offSetY; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	float GetOffSetX() { return offSetX; }
	float GetOffSetY() { return offSetY; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

