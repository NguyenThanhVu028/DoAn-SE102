#pragma once
//#include "Mario.h"
#include "MovableGameObject.h"
#include "debug.h"
#include <vector>
class CMarioHead : public CMovableGameObject
{
	friend class CMario;
	float width, height;
	std::vector<LPCOLLISIONEVENT> hitBlocks;		//Check if Mario's head hit any thing (only check if e->ny > 0)
public:
	CMarioHead(float x, float y, float width = 14, float height = 2) : CMovableGameObject(x, y){
		this->width = width; this->height = height;
		hitBlocks.clear();
	}
	void SetPosition(float x, float y) {
	}
	void Render(){}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsBlocking() { return 0; }
	void ClearHitBlocks();
	void ProcessHitBlocks();
	void ProcessCollision(DWORD dt);
};

