#pragma once
#include "GameObject.h"
class CMultiTilesBlock : public CGameObject
{
protected:
	float cellWidth, cellHeight;
	int width, height;
	int spriteIdTL, spriteIdT, spriteIdTR, spriteIdML, spriteIdM, spriteIdMR, spriteIdBL, spriteIdB, spriteIdBR;
public:
	CMultiTilesBlock(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height) {
		this->x = x; this->y = y;
		this->cellHeight = cellHeight; this->cellWidth = cellWidth;
		this->width = width; this->height = height;
	}
	CMultiTilesBlock(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height,
		int spriteIdTL, int spriteIdT, int spriteIdTR,
		int spriteIdML, int spriteIdM, int spriteIdMR,
		int spriteIdBL, int spriteIdB, int spriteIdBR) {
		this->x = x; this->y = y;
		this->cellHeight = cellHeight; this->cellWidth = cellWidth;
		this->width = width; this->height = height;
		this->spriteIdTL = spriteIdTL; this->spriteIdT = spriteIdT; this->spriteIdTR = spriteIdTR;
		this->spriteIdML = spriteIdML; this->spriteIdM = spriteIdM; this->spriteIdMR = spriteIdMR;
		this->spriteIdBL = spriteIdBL; this->spriteIdB = spriteIdB; this->spriteIdBR = spriteIdBR;
	}
	virtual void Render();
	virtual void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int GetSpriteIdToDraw(int w, int h);

	virtual int IsCollidable() { return 0; };
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual int IsBlocking() { return 1; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }
};

