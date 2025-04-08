#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Game.h"
class CSolidPlatform : public CGameObject
{
	float cellWidth, cellHeight;
	int width, height;
	int spriteIdTL, spriteIdT, spriteIdTR, spriteIdML, spriteIdM, spriteIdMR, spriteIdBL, spriteIdB, spriteIdBR;
public:
	CSolidPlatform(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height,
		int spriteIdTL, int spriteIdT, int spriteIdTR,
		int spriteIdML, int spriteIdM, int spriteIdMR,
		int spriteIdBL, int spriteIdB, int spriteIdBR) :CGameObject(x, y) 
	{
		this->cellHeight = cellHeight; this->cellWidth = cellWidth;
		this->width = width; this->height = height;
		this->spriteIdTL = spriteIdTL; this->spriteIdT = spriteIdT; this->spriteIdTR = spriteIdTR;
		this->spriteIdML = spriteIdML; this->spriteIdM = spriteIdM; this->spriteIdMR = spriteIdMR;
		this->spriteIdBL = spriteIdBL; this->spriteIdB = spriteIdB; this->spriteIdBR = spriteIdBR;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetSpriteIdToDraw(int w, int h);

	int IsDirectionColliable(float nx, float ny);

	void RenderBoundingBox();
};

