#include "Background.h"
void CBackground::Render() {
	for (auto detail : tilesList) {
		CSprite* sprite = CSprites::GetInstance()->Get(detail->GetSpriteId());
		for (int i = 0; i < detail->GetWidth(); i++) {
			for (int j = 0; j < detail->GetHeight(); j++) {
				float tempX = detail->GetX() + detail->GetCellWidth() * 0.5f + i * detail->GetCellWidth();
				float tempY = detail->GetY() + detail->GetCellHeight() * 0.5f + j * detail->GetCellHeight();
				sprite->Draw(tempX, tempY);
			}
		}
	}
}

void CBackground::AddDetail(int spriteId, float x, float y, float cellWidth, float cellHeight, float width, float height) {
	tilesList.push_back(new CTileDetail(spriteId, x, y, cellWidth, cellHeight, width, height));
}

void CBackground::Clear() {
	for (auto i : tilesList) delete i;
	tilesList.clear();
}