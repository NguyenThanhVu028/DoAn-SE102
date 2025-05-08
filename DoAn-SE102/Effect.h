#pragma once
#include <Windows.h>
#include "Animation.h"

class CEffect
{
protected:
	float x, y;
	ULONGLONG duration;
	bool isEnabled;
	LPANIMATION ani = NULL;
	ULONGLONG existing_start;
public:
	CEffect(float x, float y, ULONGLONG duration) {
		this->x = x; this->y = y;
		ReEnable();
		this->duration = duration;
	}
	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	virtual void ReEnable();
	bool IsEnabled() { return isEnabled; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
};

typedef CEffect* LPEFFECT;

