#pragma once
#include "MultiTilesBlock.h"
#include "Textures.h"
#include "Game.h"
class CSolidPlatform : public CMultiTilesBlock
{
public:
	CSolidPlatform(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height,
		int spriteIdTL, int spriteIdT, int spriteIdTR,
		int spriteIdML, int spriteIdM, int spriteIdMR,
		int spriteIdBL, int spriteIdB, int spriteIdBR) :CMultiTilesBlock(x, y, cellWidth, cellHeight, width, height, spriteIdTL, spriteIdT, spriteIdTR, spriteIdML, spriteIdM, spriteIdMR, spriteIdBL, spriteIdB, spriteIdBR){}
	bool AllowOverlap() { return false; }
};

