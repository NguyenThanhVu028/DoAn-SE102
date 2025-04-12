#include "Pipe.h"

//int CPipe::GetSpriteIdToDraw(int w, int h) {
//	if (isVertical) {
//
//	}
//	else {
//
//	}
//}
void CPipe::LoadSpriteId() {
	if (isVertical) {
		spriteIdML = PIPE_VERTICAL_BL;
		spriteIdMR = PIPE_VERTICAL_BR;
		if (endSide == 0) {
			spriteIdTL = PIPE_VERTICAL_TL; spriteIdTR = PIPE_VERTICAL_TR;
			spriteIdBL = PIPE_VERTICAL_BL; spriteIdBR = PIPE_VERTICAL_BR;
		}
		else if (endSide == 1) {
			spriteIdTL = PIPE_VERTICAL_BL; spriteIdTR = PIPE_VERTICAL_BR;
			spriteIdBL = PIPE_VERTICAL_TL; spriteIdBR = PIPE_VERTICAL_TR;
		}
		else {
			spriteIdTL = spriteIdBL = PIPE_VERTICAL_TL;
			spriteIdTR = spriteIdBR = PIPE_VERTICAL_TR;
		}
	}
	else {
		spriteIdT = PIPE_HORIZONTAL_TL;
		spriteIdB = PIPE_HORIZONTAL_BR;
		if (endSide == 0) {
			spriteIdTL = PIPE_HORIZONTAL_TL; spriteIdBL = PIPE_HORIZONTAL_BL;
			spriteIdTR = PIPE_HORIZONTAL_TR; spriteIdBR = PIPE_HORIZONTAL_BR;
		}
		else if (endSide == 1) {
			spriteIdTL = PIPE_HORIZONTAL_TR; spriteIdBL = PIPE_HORIZONTAL_BR;
			spriteIdTR = PIPE_HORIZONTAL_TL; spriteIdBR = PIPE_HORIZONTAL_BL;
		}
		else {
			spriteIdTL = spriteIdTR = PIPE_HORIZONTAL_TL;
			spriteIdBL = spriteIdBR = PIPE_HORIZONTAL_BL;
		}
	}
}