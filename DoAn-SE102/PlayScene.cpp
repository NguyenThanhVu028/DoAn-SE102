#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"

#include "MarioKeyEventHandler.h"
#include "debug.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	mapLength = mapHeight = 0;
	background = new CBackground();
	background->Clear();
	CGameObjectsManager::GetInstance()->Clear();
	key_handler = new CMarioKeyEventHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_PROPERTIES 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 4)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		float offSetX = atof(tokens[i + 2].c_str());
		float offSetY = atof(tokens[i + 3].c_str());
		ani->Add(sprite_id, frame_time, offSetX, offSetY);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (CGameObjectsManager::GetInstance()->GetPlayer()!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y);
		CGameObjectsManager::GetInstance()->SetPlayer(obj);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case OBJECT_TYPE_SOLID_PLATFORM:
	{
		if (tokens.size() < 16) break;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = (int)atoi(tokens[5].c_str());
		int height = (int)atoi(tokens[6].c_str());
		int spriteIdTL = (int)atoi(tokens[7].c_str());
		int spriteIdT = (int)atoi(tokens[8].c_str());
		int spriteIdTR = (int)atoi(tokens[9].c_str());
		int spriteIdML = (int)atoi(tokens[10].c_str());
		int spriteIdM = (int)atoi(tokens[11].c_str());
		int spriteIdMR = (int)atoi(tokens[12].c_str());
		int spriteIdBL = (int)atoi(tokens[13].c_str());
		int spriteIdB = (int)atoi(tokens[14].c_str());
		int spriteIdBR = (int)atoi(tokens[15].c_str());

		obj = new CSolidPlatform(x, y,
			cell_width, cell_height,
			width, height,
			spriteIdTL, spriteIdT, spriteIdTR,
			spriteIdML, spriteIdM, spriteIdMR,
			spriteIdBL, spriteIdB, spriteIdBR);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	}
	case OBJECT_TYPE_EMPTY_QUESTIONBLOCK:
		obj = new CQuestionBlock(x, y);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	case OBJECT_TYPE_COIN_QUESTIONBLOCK:
		obj = new CCoinQuestionBlock(x, y);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	case OBJECT_TYPE_LEVELUP_QUESTIONBLOCK:
		obj = new CLevelUpQuestionBlock(x, y);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	case OBJECT_TYPE_BACKGROUND:
		if (tokens.size() < 8) break;
		background->AddDetail((int)atoi(tokens[3].c_str()), x, y, (float)atof(tokens[4].c_str()), (float)atof(tokens[5].c_str()), (float)atof(tokens[6].c_str()), (float)atof(tokens[7].c_str()));
		break;
	case OBJECT_TYPE_HARD_BLOCK:
		obj = new CHardBlock(x, y);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
	case OBJECT_TYPE_COLOR_BLOCK:
	{
		if (tokens.size() < 8) break;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = (int)atoi(tokens[5].c_str());
		int height = (int)atoi(tokens[6].c_str());
		int color = (int)atoi(tokens[7].c_str());

		obj = new CColorBlock(x, y,
			cell_width, cell_height,
			width, height,
			color);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		if (tokens.size() < 8) break;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = (int)atoi(tokens[5].c_str());
		bool isVertical = (bool)atoi(tokens[6].c_str());
		int endSide = (int)atoi(tokens[7].c_str());

		obj = new CPipe(x, y, cell_width, cell_height, length, isVertical, endSide);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	}
	case OBJECT_TYPE_NORMAL_PIRANHA_PLANT_PIPE:
	{
		if (tokens.size() < 9) break;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = (int)atoi(tokens[5].c_str());
		bool isVertical = (bool)atoi(tokens[6].c_str());
		int endSide = (int)atoi(tokens[7].c_str());
		int type = (int)atoi(tokens[8].c_str());

		obj = new CNormalPiranhaPlantPipe(x, y, cell_width, cell_height, length, isVertical, endSide, type);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	}
	case OBJECT_TYPE_FIRE_PIRANHA_PLANT_PIPE:
	{
		if (tokens.size() < 9) break;
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = (int)atoi(tokens[5].c_str());
		bool isVertical = (bool)atoi(tokens[6].c_str());
		int endSide = (int)atoi(tokens[7].c_str());
		int type = (int)atoi(tokens[8].c_str());

		obj = new CFirePiranhaPlantPipe(x, y, cell_width, cell_height, length, isVertical, endSide, type);
		CGameObjectsManager::GetInstance()->AddStaticObject(obj);
		break;
	}
	case OBJECT_TYPE_SPAWNER_GOOMBA:
	{
		if (tokens.size() < 3) return;
		int direction = (int)atoi(tokens[3].c_str());

		auto o = new CGoombaSpawner(x, y, direction);
		CGameObjectsManager::GetInstance()->AddSpawner(o);
	}
		break;

	case OBJECT_TYPE_SPAWNER_RED_GOOMBA:
	{
		if (tokens.size() < 3) return;
		int direction = (int)atoi(tokens[3].c_str());

		auto o = new CRedGoombaSpawner(x, y, direction);
		CGameObjectsManager::GetInstance()->AddSpawner(o);
	}
		break;
	case OBJECT_TYPE_SPAWNER_RED_KOOPA_TROOPA:
	{
		if (tokens.size() < 4) return;
		int direction = (int)atoi(tokens[3].c_str());

		auto o = new CRedKoopaTroopaSpawner(x, y, direction);
		CGameObjectsManager::GetInstance()->AddSpawner(o);
	}
	break;
	case OBJECT_TYPE_SPAWNER_GREEN_KOOPA_TROOPA:
	{
		if (tokens.size() < 5) return;
		int direction = (int)atoi(tokens[3].c_str());
		bool hasWing = (bool)atoi(tokens[4].c_str());

		auto o = new CGreenKoopaTroopaSpawner(x, y, direction, hasWing);
		CGameObjectsManager::GetInstance()->AddSpawner(o);
	}
	break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
}

void CPlayScene::_ParseSection_PROPERTIES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	int type = atoi(tokens[0].c_str());
	
	switch (type) {
	case SCENE_PROPERTY_LENGTH:
		mapLength = (float)atof(tokens[1].c_str());
		break;
	case SCENE_PROPERTY_HEIGHT:
		mapHeight = (float)atof(tokens[1].c_str());
		break;
	case SCENE_PROPERTY_TIMER:
		CGame::GetInstance()->SetMaxTime((int)atoi(tokens[1].c_str()));
		break;
	}
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);


	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[PROPERTIES]") { section = SCENE_SECTION_PROPERTIES; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_PROPERTIES: _ParseSection_PROPERTIES(line); break;
		}
	}

	f.close();
	CGame::GetInstance()->ResetTimer();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	CGameObjectsManager::GetInstance()->Update(dt);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (CGameObjectsManager::GetInstance()->GetPlayer() == NULL) return;
	CGame *game = CGame::GetInstance();

	// Update camera to follow mario
	//float cx, cy;
	//CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(cx, cy);
	//cx -= game->GetBackBufferWidth() / 2;
	//cy -= game->GetBackBufferHeight() / 2;

	float cX, cY; game->GetCamPos(cX, cY);
	float pX, pY; CGameObjectsManager::GetInstance()->GetPlayer()->GetPosition(pX, pY);

	if (pX > cX + game->GetBackBufferWidth() * 0.5f + CAMERA_FOLLOW_DISTANCE * 0.5f) cX = pX - (game->GetBackBufferWidth() * 0.5f + CAMERA_FOLLOW_DISTANCE * 0.5f);
	else if (pX < cX + game->GetBackBufferWidth() * 0.5f - CAMERA_FOLLOW_DISTANCE * 0.5f) cX = pX - (game->GetBackBufferWidth() * 0.5f - CAMERA_FOLLOW_DISTANCE * 0.5f);

	if (cX < 0) cX = 0;
	if (cX > mapLength - CGame::GetInstance()->GetBackBufferWidth()) cX = mapLength - CGame::GetInstance()->GetBackBufferWidth();

	CGame::GetInstance()->SetCamPos(cX, 0.0f /*cy*/);

	//Remove objects that are deleted
	PurgeDeletedObjects();

	if (!CGame::GetInstance()->IsFrozen()) UIManager::Update(dt);
}

void CPlayScene::Render()
{
	background->Render();
	CGameObjectsManager::GetInstance()->Render();
	UIManager::Render();
}

/*
*	Clear all objects from this scene
*/
//void CPlayScene::Clear()
//{
//	vector<LPGAMEOBJECT>::iterator it;
//	for (it = objects.begin(); it != objects.end(); it++)
//	{
//		delete (*it);
//	}
//	objects.clear();
//}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	//for (int i = 0; i < objects.size(); i++)
	//	delete objects[i];

	//objects.clear();
	//player = NULL;
	CGameObjectsManager::GetInstance()->Clear();
	background->Clear();

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::PurgeDeletedObjects()
{
	CGameObjectsManager::GetInstance()->PurgeDeletedObjects();
}