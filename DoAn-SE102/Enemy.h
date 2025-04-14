#pragma once
#include "MovableGameObject.h"
class CEnemy : public CMovableGameObject
{
public:
	CEnemy(float x, float y) : CMovableGameObject(x, y){}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;
	virtual void Update(DWORD dt) {}

	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual int IsBlocking() { return 0; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	virtual bool IsDead() = 0;
};

