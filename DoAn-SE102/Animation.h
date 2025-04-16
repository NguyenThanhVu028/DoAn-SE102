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

	float ratio;	//ratio between original duration with new duration (specified by SetDuration(int duration) function

public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; lastFlickeringTime = GetTickCount64(); isFlickering = false; ratio = 1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, DWORD flickering_time = 0);
	void Render1Frame(float x, float y);
	void RenderByDuration(float x, float y, DWORD flickering_time = 0);
	void SetDuration(int duration);
	void Reset();
};

typedef CAnimation* LPANIMATION;