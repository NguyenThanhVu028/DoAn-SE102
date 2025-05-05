#pragma once
#include "MovableGameObject.h"
#include "MarioAniIds.h"
#include <vector>

#define MARIO_TAIL_WIDTH 11
#define MARIO_TAIL_HEIGHT 4

class CMarioTail : public CMovableGameObject
{
	friend class CMario;
	std::vector<LPCOLLISIONEVENT> hitObjects;
	bool isEnabled;
public:
	CMarioTail(float x, float y) : CMovableGameObject(x, y) {
		isEnabled = false;
	}
	void SetEnable(bool t) { isEnabled = t; }
	void SetPosition(float x, float y) {}
	void Render() {
		CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_DIE)->Render(x, y);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsBlocking() { return 0; }
	void ClearHitObjects();
	void ProcessHitObjects();
	void ProcessCollision(DWORD dt);
};

