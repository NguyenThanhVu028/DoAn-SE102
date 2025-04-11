#pragma once
#include <vector>
#include "Sprites.h"
class CBackground
{
	class CTileDetail {
		int spriteId;
		float x, y;
		float cellWidth, cellHeight;
		float width, height;
	public:
		CTileDetail(int spriteId, float x, float y, float cellWidth, float cellHeight, float width, float height) {
			this->spriteId = spriteId;
			this->x = x; this->y = y;
			this->cellWidth = cellWidth; this->cellHeight = cellHeight;
			this->width = width; this->height = height;
		}
		int GetSpriteId() { return spriteId; }
		float GetX(){ return x; }
		float GetY() { return y; }
		float GetCellWidth() { return cellWidth; }
		float GetCellHeight() { return cellHeight; }
		float GetWidth() { return width; }
		float GetHeight() { return height; }
	};
	std::vector<CTileDetail*> tilesList;
public:
	void Render();
	void AddDetail(int spriteId, float x, float y, float cellWidth, float cellHeight, float width, float height);
	void Clear();
};

