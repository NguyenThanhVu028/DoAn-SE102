#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"

#define MARIO_WALKING_SPEED 0,1f
#define MARIO_RUNNING_SPEED 0,2f

#define MARIO_WALKING_ACCEL_X 0.0005f
#define MARIO_RUNNING_ACCEL_X 0.0007f

#define MARIO_JUMP_SPEED 0.5f
#define MARIO_JUMP_RUN_SPEED 0.6f

#define MARIO_GRAVITY 0.002f

#define MARIO_JUMP_DEFLECT_SPEED 0.4f

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

enum MarioState { DIE, IDLE, SIT };
enum MarioLevel { SMALL, BIG, FOX };

class CMario : public CMovableGameObject
{
	MarioState state;
	MarioLevel level;
	float maxVx;
	BOOLEAN isGrounded;

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		state = MarioState::IDLE;
		level = MarioLevel::SMALL;
		ay = MARIO_GRAVITY;
		//vy = -0.1f;
	}

	void Update(DWORD dt);
	void Render();

	void SetState(MarioState state);
	MarioState GetState() { return state; }

	void SetLevel(MarioLevel level) { this->level = level; }
	MarioLevel GetLevel() { return level; }

	int IsCollidable() { return state != MarioState::DIE; }
	int IsBlocking() { return true; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

