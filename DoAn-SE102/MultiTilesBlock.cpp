#include "MultiTilesBlock.h"
#include "Game.h"
void CMultiTilesBlock::Render() {
	if (width <= 0 || height <= 0) return;
	CSprites* sprites = CSprites::GetInstance();
	int spriteIdToDraw;
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			float cX, cY; CGame::GetInstance()->GetCamPos(cX, cY);
			int screenWidth = CGame::GetInstance()->GetBackBufferWidth(), screenHeight = CGame::GetInstance()->GetBackBufferHeight();
			float tempX = x + cellWidth / 2.0f + w * cellWidth, tempY = y + cellHeight / 2.0f + h * cellHeight;
			if (tempX < cX - cellWidth * 0.5f || tempX > cX + screenWidth + cellWidth * 0.5f) continue;
			if (tempY < cY - cellHeight * 0.5f || tempY > cY + screenHeight + cellHeight * 0.5f) continue;
			spriteIdToDraw = GetSpriteIdToDraw(w, h);
			sprites->Get(spriteIdToDraw)->Draw(tempX, tempY);
		}
	}
}

int CMultiTilesBlock::GetSpriteIdToDraw(int w, int h) {
	if (w == 0 && h == 0) return spriteIdTL;
	if (w == width - 1 && h == 0) return spriteIdTR;
	if (w == 0 && h == height - 1) return spriteIdBL;
	if (w == width - 1 && h == height - 1) return spriteIdBR;
	if (w == 0) return spriteIdML;
	if (w == width - 1) return spriteIdMR;
	if (h == 0) return spriteIdT;
	if (h == height - 1) return spriteIdB;
	return spriteIdM;
}

void CMultiTilesBlock::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = l + cellWidth * width;
	b = t + cellHeight * height;
}