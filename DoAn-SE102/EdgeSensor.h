#pragma once
#include "MovableGameObject.h"
#include "debug.h"
class CEdgeSensor : public CMovableGameObject
{
	friend class CRedKoopaTroopa;
	float width, height;
	bool rightEdge, leftEdge;
	std::vector<LPCOLLISIONEVENT> touchedBlocks;		//Check if Mario's head hit any thing (only check if e->ny < 0)
public:
	CEdgeSensor(float x, float y, float width = 16, float height = 2) : CMovableGameObject(x, y) {
		this->width = width; this->height = height;
		touchedBlocks.clear();
	}
	void SetPosition(float x, float y) {
	}
	void Render() {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsBlocking() { return 0; }
	void ProcessCollision(DWORD dt);
	void ClearTouchedBlocks();
	void ProcessTouchedBlocks();

	bool RightEdge() { return rightEdge; };
	bool LeftEdge() { return leftEdge; };
};

