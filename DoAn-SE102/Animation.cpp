#include "Animation.h"
#include "debug.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, DWORD flickering_time)
{
	ULONGLONG now = GetTickCount64();

	//Flickering effect (used when Mario is untouchable)
	if (flickering_time == 0) isFlickering = false;
	else if (now - lastFlickeringTime > flickering_time) {
		isFlickering = (isFlickering) ? false: true;
		lastFlickeringTime = now;
	}

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			//if (now - lastFrameTime < t + flickering_time) return;
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	if (isFlickering) return;
	frames[currentFrame]->GetSprite()->Draw(x, y);
}

void CAnimation::RenderByDuration(float x, float y, DWORD flickering_time) {
	ULONGLONG now = GetTickCount64();

	//Flickering effect (used when Mario is untouchable)
	if (flickering_time == 0) isFlickering = false;
	else if (now - lastFlickeringTime > flickering_time) {
		isFlickering = (isFlickering) ? false : true;
		lastFlickeringTime = now;
	}

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime() * ratio;
		if (now - lastFrameTime > t)
		{
			//if (now - lastFrameTime < t + flickering_time) return;
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	if (isFlickering) return;
	frames[currentFrame]->GetSprite()->Draw(x, y);
}

void CAnimation::Render1Frame(float x, float y) {
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
	}
	lastFrameTime = now;
	frames[currentFrame]->GetSprite()->Draw(x, y);
}

void CAnimation::Reset() {
	currentFrame = 0;
	lastFrameTime = GetTickCount64();
}

void CAnimation::SetDuration(int duration) {
	int oldDuration = 0;
	for (auto i : frames) oldDuration += i->GetTime();
	ratio = 1.0f * duration / oldDuration;
}

