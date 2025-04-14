#pragma once
#include "QuestionBlock.h"
#include "GameObject.h"
#include "Mushroom.h"
#include "Leaf.h"
class CLevelUpQuestionBlock : public CQuestionBlock
{
	CLevelUpItem* item = NULL;
	bool hasSummonedItem;
	int nx;
public:
	CLevelUpQuestionBlock(float x, float y) : CQuestionBlock(x, y) { hasSummonedItem = false; nx = 1; }
	void Render();
	void Update(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

