#pragma once
#include "MovableGameObject.h"

class CEnemy : public CMovableGameObject
{
protected:
	bool isKilled;		//When enemy is killed -> Spawner will delete it
	bool isEnabled;		//When enemy is out of screen view -> Spawner can respawn it
	ULONGLONG untouchable_start;	//untouchable timer
public:
	CEnemy(float x, float y, int nx = 1) : CMovableGameObject(x, y) { isEnabled = true; isKilled = false; this->nx = nx; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;
	virtual void Update(DWORD dt) {}

	virtual int IsCollidable() { return 1; }
	virtual void OnNoCollision(DWORD dt) {}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}
	virtual void OnCollisionWithMario(LPCOLLISIONEVENT e) {}
	virtual void OnCollisionWithShell(LPCOLLISIONEVENT e) {}
	virtual int IsBlocking() { return 0; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	virtual bool IsUntouchable() { return false; }
	virtual bool IsDead() = 0;
	virtual void SetEnable(bool t) { isEnabled = t; }
	virtual bool IsEnabled() { return isEnabled; }
	virtual bool IsKilled() { return isKilled; }
};

