#pragma once
#include "MultiTilesBlock.h"

#define PIPE_ACTIVE_ZONE_OFFSET 8

#define PIPE_VERTICAL_TL 20101
#define PIPE_VERTICAL_TR 20102
#define PIPE_VERTICAL_BL 20103
#define PIPE_VERTICAL_BR 20104

#define PIPE_HORIZONTAL_TL 20105
#define PIPE_HORIZONTAL_TR 20106
#define PIPE_HORIZONTAL_BL 20107
#define PIPE_HORIZONTAL_BR 20108

class CPipe : public CMultiTilesBlock
{
protected:
	bool isVertical;	//The pipe is vertical or horizontal
	int endSide;			//Which side does the pipe end	1: top / left	2: bottom / right	3: both
public:
	CPipe(float x, float y, float cellWidth, float cellHeight, int length, bool isVertical, int side) : CMultiTilesBlock(x, y, cellWidth, cellHeight, 0, 0) {
		this->isVertical = isVertical;
		this->endSide = side;
		if (isVertical) { width = 2; height = length; }
		else { width = length; height = 2; }
		LoadSpriteId();
	}
	virtual void Update(DWORD dt) {}
	virtual void Render() { CMultiTilesBlock::Render(); }
	virtual void LoadSpriteId();
	bool AllowOverlap() { return false; }
};

