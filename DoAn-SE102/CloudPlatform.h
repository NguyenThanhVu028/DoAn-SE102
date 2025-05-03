#pragma once
#include "MultiTilesBlock.h"

#define CLOUD_PLATFORM 20111

class CCloudPlatform : public CMultiTilesBlock
{
public:
	CCloudPlatform(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height) : CMultiTilesBlock(x, y, cellWidth, cellHeight, width, height) {
		spriteIdTL = spriteIdT = spriteIdTR = CLOUD_PLATFORM;
		spriteIdML = spriteIdM = spriteIdMR = CLOUD_PLATFORM;
		spriteIdBL = spriteIdB = spriteIdBR = CLOUD_PLATFORM;
	}
	int IsDirectionColliable(float nx, float ny) {
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
	bool AllowOverlap() { return true; }
};

