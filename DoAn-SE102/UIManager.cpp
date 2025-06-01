#include "UIManager.h"
CUIManager* CUIManager::instance = NULL;
UI* CUIManager::ui_Instance = NULL;

void CUIManager::Update(DWORD dt) {
	if (ui_Instance != NULL) ui_Instance->Update(dt);
}

void CUIManager::Render() {
	if (ui_Instance != NULL) ui_Instance->Render();
}

CUIManager* CUIManager::GetInstance() {
	if (instance == NULL) instance = new CUIManager();
	return instance;
}