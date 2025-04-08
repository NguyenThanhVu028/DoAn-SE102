#include "SolidPlatform.h"

void CSolidPlatform::Render() {
	if (width <= 0 || height <= 0) return;
	CSprites* sprites = CSprites::GetInstance();
	int spriteIdToDraw;
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			spriteIdToDraw = GetSpriteIdToDraw(w, h);
			sprites->Get(spriteIdToDraw)->Draw(x + cellWidth / 2.0f + w * cellWidth, y + cellHeight / 2.0f + h * cellHeight);
		}
	}
	RenderBoundingBox();
}

int CSolidPlatform::GetSpriteIdToDraw(int w, int h) {
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

void CSolidPlatform::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = l + cellWidth * width;
	b = t + cellHeight * height;
	//l = 0; t = 100; r = 300; b = 150;
}

int CSolidPlatform::IsDirectionColliable(float nx, float ny) {
	return 1;
}

void CSolidPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(x - cx + width * cellWidth / 2.0f, y - cy + height * cellHeight / 2.0f, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}