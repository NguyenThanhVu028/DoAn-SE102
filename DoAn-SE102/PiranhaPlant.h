#pragma once
#include "GameObject.h"
#include "GameObjectsManager.h"
#include "Mario.h"

#define PIRANHA_PLANT_HEIGHT 32
#define PIRANHA_PLANT_WIDTH 16

class CPiranhaPlant : public CEnemy
{
protected:
	float oriX, oriY;

	bool isActive;
	bool hasRised;
	float risingHeight;
	ULONGLONG risingTime;
	ULONGLONG waitingTime;
	ULONGLONG checkPoint;
public:
	CPiranhaPlant(float x, float y) : CEnemy(x, y) { isActive = true; oriX = x; oriY = y; checkPoint = CGame::GetInstance()->GetTickCount(); }

	void Update(DWORD dt);
	virtual void Render() = 0;
	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithShell(LPCOLLISIONEVENT e);

	void SetActive(bool t) { isActive = t; }
	bool IsRising();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	bool IsDead() override;
};

