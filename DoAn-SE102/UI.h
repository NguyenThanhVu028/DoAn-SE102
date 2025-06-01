#pragma once
#include <Windows.h>
class UI
{	
public:
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void StartFading() {};
	virtual void StartBrightening() {};
};

