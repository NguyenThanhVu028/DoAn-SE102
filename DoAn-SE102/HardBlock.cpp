#include "HardBlock.h"
#include "Game.h"
void CHardBlock::Render() {
	float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
	int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x < cX - HARD_BLOCK_WIDTH || x > cX + screenWidth) return;
	if (y < cY - HARD_BLOCK_HEIGHT || y > cY + screenHeight + HARD_BLOCK_HEIGHT) return;
	CSprites::GetInstance()->Get(HARD_BLOCK_SPRITE_ID)->Draw(x + HARD_BLOCK_WIDTH * 0.5f, y + HARD_BLOCK_HEIGHT * 0.5f);
}

void CHardBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x; top = y;
	right = left + HARD_BLOCK_WIDTH;
	bottom = y + HARD_BLOCK_HEIGHT;
}