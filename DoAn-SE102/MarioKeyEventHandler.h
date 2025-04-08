#pragma once
#include "Scene.h"
#include "Mario.h"
#include "GameObjectsManager.h"
class CMarioKeyEventHandler : public CSceneKeyHandler
{
public:
	void KeyState(BYTE* state) override;
	void OnKeyDown(int KeyCode) override;
	void OnKeyUp(int KeyCode) override;
	CMarioKeyEventHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

