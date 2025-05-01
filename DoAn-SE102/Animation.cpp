#include "Animation.h"
#include "debug.h"
#include "Game.h"

void CAnimation::Add(int spriteId, DWORD time, float offSetX, float offSetY)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t, offSetX, offSetY);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, DWORD flickering_time)
{
	ULONGLONG now = CGame::GetInstance()->GetTickCount();

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
	float offSetX = frames[currentFrame]->GetOffSetX(), offSetY = frames[currentFrame]->GetOffSetY();
	frames[currentFrame]->GetSprite()->Draw(x + offSetX, y + offSetY);
}

void CAnimation::RenderOnScreen(float x, float y, DWORD flickering_time) {
	ULONGLONG now = CGame::GetInstance()->GetTickCount();

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
	float offSetX = frames[currentFrame]->GetOffSetX(), offSetY = frames[currentFrame]->GetOffSetY();
	frames[currentFrame]->GetSprite()->DrawOnScreen(x + offSetX, y + offSetY);
}

void CAnimation::RenderByDuration(float x, float y, DWORD flickering_time) {
	ULONGLONG now = CGame::GetInstance()->GetTickCount();

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
	if (isFlickering) { return; }
	float offSetX = frames[currentFrame]->GetOffSetX(), offSetY = frames[currentFrame]->GetOffSetY();
	frames[currentFrame]->GetSprite()->Draw(x + offSetX, y + offSetY);
}

void CAnimation::Render1Frame(float x, float y) {
	ULONGLONG now = CGame::GetInstance()->GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
	}
	lastFrameTime = now;
	float offSetX = frames[currentFrame]->GetOffSetX(), offSetY = frames[currentFrame]->GetOffSetY();
	frames[currentFrame]->GetSprite()->Draw(x + offSetX, y + offSetY);
}

void CAnimation::Reset() {
	currentFrame = 0;
	lastFrameTime = CGame::GetInstance()->GetTickCount();
}

void CAnimation::SetDuration(int duration) {
	if (duration == -1) ratio = 1;
	int oldDuration = 0;
	for (auto i : frames) oldDuration += i->GetTime();
	ratio = 1.0f * duration / oldDuration;
}

