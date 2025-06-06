#pragma once
#include "MovableGameObject.h"
#define DEFAULT_UNTOUCHABLE_TIME 200

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
	virtual void OnCollisionWithMarioTail(LPCOLLISIONEVENT e) {}
	virtual void OnCollisionWithBouncingBlock(LPCOLLISIONEVENT e) { CMovableGameObject::OnCollisionWithBouncingBlock(e); }
	virtual int IsBlocking() { return 0; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	virtual bool IsUntouchable() { return CGame::GetInstance()->GetTickCount() - untouchable_start < DEFAULT_UNTOUCHABLE_TIME; }
	virtual bool IsDead() = 0;
	virtual void SetEnable(bool t) { isEnabled = t; }
	virtual bool IsEnabled() { return isEnabled; }
	virtual bool IsKilled() { return isKilled; }
};

