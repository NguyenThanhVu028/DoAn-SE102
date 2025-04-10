#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"

using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	
	ULONGLONG lastFlickeringTime;
	bool isFlickering;

public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; lastFlickeringTime = GetTickCount64(); isFlickering = false; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, ULONGLONG flickering_time = 0);
	void Render1Frame(float x, float y);
	void Reset();
};

typedef CAnimation* LPANIMATION;