#pragma once
#include "GameObject.h"
class MovableGameObject : public CGameObject
{
protected:

	float vx;
	float vy;
	float ax;
	float ay;

	int nx;

public:
	MovableGameObject();
	MovableGameObject(float x, float y) : CGameObject(x, y) {
		vx = vy = 0;
		ax = ay = 0;
		nx = 1;
	}
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) override { vx = this->vx; vy = this->vy; }
	void SetAcceleration(float ax, float ay) { this->ax = ax; this->ay = ay; }
	void GetAcceleration(float& ax, float& ay) { ax = this->ax; ay = this->ay; }

	virtual void Render() = 0;
};

