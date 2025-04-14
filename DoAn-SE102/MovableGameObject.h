#pragma once
#include "GameObject.h"
class CMovableGameObject : public CGameObject
{
protected:

	float vx;
	float vy;
	float ax;
	float ay;

	int nx;

public:
	CMovableGameObject();
	CMovableGameObject(float x, float y) : CGameObject(x, y) {
		vx = vy = 0;
		ax = ay = 0;
		nx = 1;
	}
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void SetAcceleration(float ax, float ay) { this->ax = ax; this->ay = ay; }
	void GetAcceleration(float& ax, float& ay) { ax = this->ax; ay = this->ay; }
	void SetDirection(int nx) { this->nx = nx; }
	int GetDirection() { return nx; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;
	virtual void Update(DWORD dt){}

	virtual int IsCollidable() { return 0; };
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual int IsBlocking() { return 1; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

};

