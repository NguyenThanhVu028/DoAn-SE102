#pragma once
#include "Brick.h"
#include "GreenMushroom.h"
class CGreenMushroomBrick : public CBrick
{
	int nx;
	bool hasSummonedItem;
	CLevelUpItem* item;
public:
	CGreenMushroomBrick(float x, float y) : CBrick(x, y) {
		hasSummonedItem = false; item = NULL;
	}
	void Update(DWORD dt);
	void Render();
	void SpecialEffect(LPCOLLISIONEVENT e);
};

