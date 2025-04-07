#include "GameObjectsManager.h"
CGameObjectsManager* CGameObjectsManager::__instance = NULL;

CGameObjectsManager* CGameObjectsManager::GetInstance() {
	if (__instance == NULL) __instance = new CGameObjectsManager();
	return __instance;
}

void CGameObjectsManager::Update(DWORD dt) {

}
void CGameObjectsManager::Render() {

}
void CGameObjectsManager::Clear() {

}