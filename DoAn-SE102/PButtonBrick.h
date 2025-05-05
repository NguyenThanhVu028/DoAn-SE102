#pragma once
#include "Brick.h"
#include "PButton.h"
class CPButtonBrick : public CBrick
{
public:
	CPButtonBrick(float x, float y) : CBrick(x, y){}
	void SpecialEffect(LPCOLLISIONEVENT e);
};

