#include "ColorBlock.h"
void CColorBlock::LoadSpriteId() {
	switch (color) {
	case COLOR_RED:
		spriteIdTL = COLOR_BLOCK_RED_TL;
		spriteIdT = COLOR_BLOCK_RED_T;
		spriteIdTR = COLOR_BLOCK_RED_TR;
		spriteIdML = COLOR_BLOCK_RED_ML;
		spriteIdM = COLOR_BLOCK_RED_M;
		spriteIdMR = COLOR_BLOCK_RED_MR;
		spriteIdBL = COLOR_BLOCK_RED_BL;
		spriteIdB = COLOR_BLOCK_RED_B;
		spriteIdBR = COLOR_BLOCK_RED_BR;
		break;
	case COLOR_BLUE:
		spriteIdTL = COLOR_BLOCK_BLUE_TL;
		spriteIdT = COLOR_BLOCK_BLUE_T;
		spriteIdTR = COLOR_BLOCK_BLUE_TR;
		spriteIdML = COLOR_BLOCK_BLUE_ML;
		spriteIdM = COLOR_BLOCK_BLUE_M;
		spriteIdMR = COLOR_BLOCK_BLUE_MR;
		spriteIdBL = COLOR_BLOCK_BLUE_BL;
		spriteIdB = COLOR_BLOCK_BLUE_B;
		spriteIdBR = COLOR_BLOCK_BLUE_BR;
		break;
	case COLOR_GREEN:
		spriteIdTL = COLOR_BLOCK_GREEN_TL;
		spriteIdT = COLOR_BLOCK_GREEN_T;
		spriteIdTR = COLOR_BLOCK_GREEN_TR;
		spriteIdML = COLOR_BLOCK_GREEN_ML;
		spriteIdM = COLOR_BLOCK_GREEN_M;
		spriteIdMR = COLOR_BLOCK_GREEN_MR;
		spriteIdBL = COLOR_BLOCK_GREEN_BL;
		spriteIdB = COLOR_BLOCK_GREEN_B;
		spriteIdBR = COLOR_BLOCK_GREEN_BR;
		break;
	case COLOR_WHITE:
		spriteIdTL = COLOR_BLOCK_WHITE_TL;
		spriteIdT = COLOR_BLOCK_WHITE_T;
		spriteIdTR = COLOR_BLOCK_WHITE_TR;
		spriteIdML = COLOR_BLOCK_WHITE_ML;
		spriteIdM = COLOR_BLOCK_WHITE_M;
		spriteIdMR = COLOR_BLOCK_WHITE_MR;
		spriteIdBL = COLOR_BLOCK_WHITE_BL;
		spriteIdB = COLOR_BLOCK_WHITE_B;
		spriteIdBR = COLOR_BLOCK_WHITE_BR;
		break;
	case COLOR_ORANGE:
		spriteIdTL = COLOR_BLOCK_ORANGE_TL;
		spriteIdT = COLOR_BLOCK_ORANGE_T;
		spriteIdTR = COLOR_BLOCK_ORANGE_TR;
		spriteIdML = COLOR_BLOCK_ORANGE_ML;
		spriteIdM = COLOR_BLOCK_ORANGE_M;
		spriteIdMR = COLOR_BLOCK_ORANGE_MR;
		spriteIdBL = COLOR_BLOCK_ORANGE_BL;
		spriteIdB = COLOR_BLOCK_ORANGE_B;
		spriteIdBR = COLOR_BLOCK_ORANGE_BR;
		break;
	default:
		spriteIdTL = COLOR_BLOCK_RED_TL;
		spriteIdT = COLOR_BLOCK_RED_T;
		spriteIdTR = COLOR_BLOCK_RED_TR;
		spriteIdML = COLOR_BLOCK_RED_ML;
		spriteIdM = COLOR_BLOCK_RED_M;
		spriteIdMR = COLOR_BLOCK_RED_MR;
		spriteIdBL = COLOR_BLOCK_RED_BL;
		spriteIdB = COLOR_BLOCK_RED_B;
		spriteIdBR = COLOR_BLOCK_RED_BR;
		break;
	}
}

void CColorBlock::Render() {
	CMultiTilesBlock::Render();
	int spriteId;
	for (int i = 0; i < height; i++) {
		if (i == 0) spriteId = COLOR_BLOCK_SHADOW_1;
		else spriteId = COLOR_BLOCK_SHADOW_2;
		CSprites::GetInstance()->Get(spriteId)->Draw(x + width*cellWidth + SHADOW_WIDTH * 0.5f, y + SHADOW_HEIGHT * 0.5f + i * cellHeight);
	}
	for (int i = 0; i <= width; i++) {
		if (i == 0) spriteId = COLOR_BLOCK_SHADOW_3;
		else if (i == width) spriteId = COLOR_BLOCK_SHADOW_5;
		else spriteId = COLOR_BLOCK_SHADOW_4;
		CSprites::GetInstance()->Get(spriteId)->Draw(x + SHADOW_WIDTH * 0.5f + i * cellWidth, y + height*cellHeight + SHADOW_HEIGHT * 0.5f);
	}
}