#include "UIManager.h"
UI* UIManager::ui_Instance = new PlaySceneUI();

void UIManager::Update(DWORD dt) {
	if (ui_Instance != NULL) ui_Instance->Update(dt);
}

void UIManager::Render() {
	if (ui_Instance != NULL) ui_Instance->Render();
}