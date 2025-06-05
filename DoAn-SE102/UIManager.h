#pragma once
#include "PlaySceneUI.h"
class CUIManager
{
	static CUIManager* instance;
	static UI* ui_Instance;
public:
	CUIManager() {
		if (ui_Instance == NULL) ui_Instance = new CPlaySceneUI();
	}
	static CUIManager* GetInstance();
	void Update(DWORD dt);
	void Render();
	void StartFading() { ui_Instance->StartFading(); }
	void StartBrightening() { ui_Instance->StartBrightening(); }
	void StartEndGameSequence() { if (dynamic_cast<CPlaySceneUI*>(ui_Instance)) dynamic_cast<CPlaySceneUI*>(ui_Instance)->StartEndGameSequence(); }
};

