#pragma once
#include "EnterablePipe.h"

#define BLACK_PIPE_VERTICAL_TL 20171
#define BLACK_PIPE_VERTICAL_TR 20172
#define BLACK_PIPE_VERTICAL_BL 20173
#define BLACK_PIPE_VERTICAL_BR 20174

#define BLACK_PIPE_HORIZONTAL_TL 20175
#define BLACK_PIPE_HORIZONTAL_TR 20176
#define BLACK_PIPE_HORIZONTAL_BL 20177
#define BLACK_PIPE_HORIZONTAL_BR 20178

class CBlackEnterablePipe : public CEnterablePipe
{
public:
	CBlackEnterablePipe(float x, float y, float cellWidth, float cellHeight, int length, bool isVertical, int side, bool enterSide, bool type, int world_id, bool isEnabled = false)
		: CEnterablePipe(x, y, cellWidth, cellHeight, length, isVertical, side, enterSide, type, world_id, isEnabled) {
		LoadSpriteId();
	}
	void LoadSpriteId();
};

