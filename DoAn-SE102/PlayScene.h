#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "GameObjectsManager.h"
#include "SolidPlatform.h"
#include "QuestionBlock.h"
#include "CoinQuestionBlock.h"
#include "HardBlock.h"
#include "ColorBlock.h"
#include "Pipe.h"
#include "NormalPiranhaPlantPipe.h"
//#include "Brick.h"
//#include "Mario.h"
//#include "Goomba.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have a player, right? 
	//LPGAMEOBJECT player;					

	//vector<LPGAMEOBJECT> objects;
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

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

