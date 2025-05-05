#pragma once
#include "Mushroom.h"
#define GREEN_MUSHROOM_SPRITE 70031
class CGreenMushroom : public CMushroom
{
public:
	CGreenMushroom(float x, float y, int nx = 1) : CMushroom(x, y, nx){}
	void Render();
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

