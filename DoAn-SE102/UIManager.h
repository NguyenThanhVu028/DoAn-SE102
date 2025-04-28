#pragma once
#include "PlaySceneUI.h"
class UIManager
{
	static UI* ui_Instance;
public:
	static void Update(DWORD dt);
	static void Render();
};

