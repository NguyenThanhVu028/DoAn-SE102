#pragma once
#include "MultiTilesBlock.h"

//RED
#define COLOR_BLOCK_RED_TL 20041
#define COLOR_BLOCK_RED_T 20042
#define COLOR_BLOCK_RED_TR 20043
#define COLOR_BLOCK_RED_ML 20044
#define COLOR_BLOCK_RED_M 20045
#define COLOR_BLOCK_RED_MR 20046
#define COLOR_BLOCK_RED_BL 20047
#define COLOR_BLOCK_RED_B 20048
#define COLOR_BLOCK_RED_BR 20049

//BLUE
#define COLOR_BLOCK_BLUE_TL 20051
#define COLOR_BLOCK_BLUE_T 20052
#define COLOR_BLOCK_BLUE_TR 20053
#define COLOR_BLOCK_BLUE_ML 20054
#define COLOR_BLOCK_BLUE_M 20055
#define COLOR_BLOCK_BLUE_MR 20056
#define COLOR_BLOCK_BLUE_BL 20057
#define COLOR_BLOCK_BLUE_B 20058
#define COLOR_BLOCK_BLUE_BR 20059

//GREEN
#define COLOR_BLOCK_GREEN_TL 20061
#define COLOR_BLOCK_GREEN_T 20062
#define COLOR_BLOCK_GREEN_TR 20063
#define COLOR_BLOCK_GREEN_ML 20064
#define COLOR_BLOCK_GREEN_M 20065
#define COLOR_BLOCK_GREEN_MR 20066
#define COLOR_BLOCK_GREEN_BL 20067
#define COLOR_BLOCK_GREEN_B 20068
#define COLOR_BLOCK_GREEN_BR 20069

//WHITE
#define COLOR_BLOCK_WHITE_TL 20071
#define COLOR_BLOCK_WHITE_T 20072
#define COLOR_BLOCK_WHITE_TR 20073
#define COLOR_BLOCK_WHITE_ML 20074
#define COLOR_BLOCK_WHITE_M 20075
#define COLOR_BLOCK_WHITE_MR 20076
#define COLOR_BLOCK_WHITE_BL 20077
#define COLOR_BLOCK_WHITE_B 20078
#define COLOR_BLOCK_WHITE_BR 20079

//ORANGE
#define COLOR_BLOCK_ORANGE_TL 20081
#define COLOR_BLOCK_ORANGE_T 20082
#define COLOR_BLOCK_ORANGE_TR 20083
#define COLOR_BLOCK_ORANGE_ML 20084
#define COLOR_BLOCK_ORANGE_M 20085
#define COLOR_BLOCK_ORANGE_MR 20086
#define COLOR_BLOCK_ORANGE_BL 20087
#define COLOR_BLOCK_ORANGE_B 20088
#define COLOR_BLOCK_ORANGE_BR 20089

//SHADOW
#define COLOR_BLOCK_SHADOW_1 20091
#define COLOR_BLOCK_SHADOW_2 20092
#define COLOR_BLOCK_SHADOW_3 20093
#define COLOR_BLOCK_SHADOW_4 20094
#define COLOR_BLOCK_SHADOW_5 20095
#define SHADOW_WIDTH 16
#define SHADOW_HEIGHT 16

#define COLOR_RED 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_WHITE 3
#define COLOR_ORANGE 4

class CColorBlock : public CMultiTilesBlock
{
	int color;
public:
	CColorBlock(float x, float y,
		float cellWidth, float cellHeight,
		int width, int height, int color) : CMultiTilesBlock(x, y, cellWidth, cellHeight, width, height){
		this->color = color;
		LoadSpriteId();
	}
	void LoadSpriteId();
	int IsDirectionColliable(float nx, float ny){
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
	void Render();

	bool AllowOverlap() { return true; }
};

