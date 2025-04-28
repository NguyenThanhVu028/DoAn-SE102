#pragma once
#include "UI.h"
#define UI_BACKGROUND_HEIGHT 46

//spriteID
#define UI_SPRITE_BACKGROUND 100001

class PlaySceneUI : public UI
{
public: 
	void Update(DWORD dt);
	void Render();
};

