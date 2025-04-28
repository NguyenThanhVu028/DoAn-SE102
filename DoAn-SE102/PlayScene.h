#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "GameObjectsManager.h"
#include "SolidPlatform.h"
#include "QuestionBlock.h"
#include "CoinQuestionBlock.h"
#include "LevelUpQuestionBlock.h"
#include "HardBlock.h"
#include "ColorBlock.h"
#include "Pipe.h"
#include "NormalPiranhaPlantPipe.h"
#include "FirePiranhaPlantPipe.h"
#include "GoombaSpawner.h"
#include "RedGoombaSpawner.h"
#include "RedKoopaTroopaSpawner.h"
#include "UIManager.h"


class CPlayScene: public CScene
{
protected: 
	float mapLength, mapHeight;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_PROPERTIES(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	//LPGAMEOBJECT GetPlayer() { return player; }

	//void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o) {};
};

typedef CPlayScene* LPPLAYSCENE;

