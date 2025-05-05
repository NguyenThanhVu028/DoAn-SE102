#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PBUTTON_WIDTH 16
#define PBUTTON_HEIGHT 16

//Ani Ids
#define PBUTTON_ANIMATION_AVAILABLE 20141
#define PBUTTON_ANIMATION_UNAVAILABLE 20151

class CPButton : public CGameObject
{
	bool isActivated;
public:
	CPButton(float x, float y) : CGameObject(x, y) {
		isActivated = false;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return !isActivated; };
};

