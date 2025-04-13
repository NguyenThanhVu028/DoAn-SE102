#pragma once
#include "MovableGameObject.h"
class CLevelUpItem : public CMovableGameObject
{
protected:
	bool isEnabled;
public:
	CLevelUpItem(float x, float y) : CMovableGameObject(x, y) { isEnabled = false; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;
	virtual void Update(DWORD dt) {};
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	bool IsEnabled() { return isEnabled; }
	virtual void ReEnable() { isEnabled = true; };

	void Delete() { isDeleted = true; }
};

