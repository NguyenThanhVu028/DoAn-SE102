#pragma once
#include "QuestionBlock.h"
class CCoinQuestionBlock : public CQuestionBlock
{
public:
	CCoinQuestionBlock(float x, float y) : CQuestionBlock(x, y){}
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

