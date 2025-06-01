#include "BlackEnterablePipe.h"

void CBlackEnterablePipe::LoadSpriteId() {
	if (isVertical) {
		spriteIdML = BLACK_PIPE_VERTICAL_BL;
		spriteIdMR = BLACK_PIPE_VERTICAL_BR;
		if (endSide == 0) {
			spriteIdTL = BLACK_PIPE_VERTICAL_TL; spriteIdTR = BLACK_PIPE_VERTICAL_TR;
			spriteIdBL = BLACK_PIPE_VERTICAL_BL; spriteIdBR = BLACK_PIPE_VERTICAL_BR;
		}
		else if (endSide == 1) {
			spriteIdTL = BLACK_PIPE_VERTICAL_BL; spriteIdTR = BLACK_PIPE_VERTICAL_BR;
			spriteIdBL = BLACK_PIPE_VERTICAL_TL; spriteIdBR = BLACK_PIPE_VERTICAL_TR;
		}
		else if (endSide == 2) {
			spriteIdTL = spriteIdBL = BLACK_PIPE_VERTICAL_TL;
			spriteIdTR = spriteIdBR = BLACK_PIPE_VERTICAL_TR;
		}
		else {
			spriteIdTL = spriteIdBL = BLACK_PIPE_VERTICAL_BL;
			spriteIdTR = spriteIdBR = BLACK_PIPE_VERTICAL_BR;
		}
	}
	else {
		spriteIdT = BLACK_PIPE_HORIZONTAL_TL;
		spriteIdB = BLACK_PIPE_HORIZONTAL_BR;
		if (endSide == 0) {
			spriteIdTL = BLACK_PIPE_HORIZONTAL_TL; spriteIdBL = BLACK_PIPE_HORIZONTAL_BL;
			spriteIdTR = BLACK_PIPE_HORIZONTAL_TR; spriteIdBR = BLACK_PIPE_HORIZONTAL_BR;
		}
		else if (endSide == 1) {
			spriteIdTL = BLACK_PIPE_HORIZONTAL_TR; spriteIdBL = BLACK_PIPE_HORIZONTAL_BR;
			spriteIdTR = BLACK_PIPE_HORIZONTAL_TL; spriteIdBR = BLACK_PIPE_HORIZONTAL_BL;
		}
		else {
			spriteIdTL = spriteIdTR = BLACK_PIPE_HORIZONTAL_TL;
			spriteIdBL = spriteIdBR = BLACK_PIPE_HORIZONTAL_BL;
		}
	}
}