#pragma once
#include "GameObject.h"
#include "Sprites.h"

#define HARD_BLOCK_SPRITE_ID 20031

#define HARD_BLOCK_WIDTH 16
#define HARD_BLOCK_HEIGHT 16

class CHardBlock : public CGameObject
{
public:
	CHardBlock(float x, float y) : CGameObject(x, y){ }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

