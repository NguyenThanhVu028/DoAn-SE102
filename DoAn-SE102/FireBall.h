#pragma once
#include "GameObject.h"
#include "MovableGameObject.h"

#define FIREBALL_WIDTH 8
#define FIREBALL_HEIGHT 8

#define FIREBALL_SPEED 0.1f

//Animation Ids
#define FIREBALL_ANIMATION_LEFT 60011
#define FIREBALL_ANIMATION_RIGHT 60021

class CFireBall : public CMovableGameObject
{
	bool isEnabled;
	bool angle;
public:
	CFireBall(float x, float y) : CMovableGameObject(x, y) {
		SetAngle(10); isEnabled = true;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	bool IsEnabled() { return isEnabled; }
	void ReEnable() { isEnabled = true; }
	void SetAngle(float x);
};

typedef CFireBall* LPFIREBALL;

