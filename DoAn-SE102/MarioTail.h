#pragma once
#include "MovableGameObject.h"
#include <vector>

#define MARIO_TAIL_WIDTH 8
#define MARIO_TAIL_HEIGHT 2

class CMarioTail : public CMovableGameObject
{
	friend class CMario;
	std::vector<LPCOLLISIONEVENT> hitBlocks;
	bool isEnabled;
public:
	CMarioTail(float x, float y) : CMovableGameObject(x, y) {
		isEnabled = false;
	}
	void SetEnable(bool t) { isEnabled = t; }
	void SetPosition(float x, float y) {}
	void Render() {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsBlocking() { return 0; }
	void ClearHitBlocks();
	void ProcessHitBlocks();
	void ProcessCollision(DWORD dt);
};

