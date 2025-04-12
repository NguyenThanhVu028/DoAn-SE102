#include "HardBlock.h"

void CHardBlock::Render() {
	CSprites::GetInstance()->Get(HARD_BLOCK_SPRITE_ID)->Draw(x + HARD_BLOCK_WIDTH * 0.5f, y + HARD_BLOCK_HEIGHT * 0.5f);
}

void CHardBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x; top = y;
	right = left + HARD_BLOCK_WIDTH;
	bottom = y + HARD_BLOCK_HEIGHT;
}