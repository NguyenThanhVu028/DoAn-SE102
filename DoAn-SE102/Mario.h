#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"

#define MARIO_WALKING_SPEED 0.1f
#define MARIO_RUNNING_SPEED 0.2f

#define MARIO_WALKING_ACCEL_X 0.000075f
#define MARIO_RUNNING_ACCEL_X 0.0001f

#define MARIO_DECEL_X 0.0001f
#define MARIO_BRAKE_DECEL MARIO_DECEL_X * 3.0f

#define MARIO_JUMP_SPEED 0.175f
#define MARIO_JUMP_TIME 230
#define MARIO_JUMP_RUN_SPEED 0.6f
#define MARIO_JUMP_ACCEL 0.001f

#define MARIO_GRAVITY 0.0006f

#define MARIO_JUMP_DEFLECT_SPEED 0.4f

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

enum MarioState { DIE, IDLE, SIT, JUMP, RELEASE_JUMP, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, JUMP_WALK_RIGHT, JUMP_WALK_LEFT };
enum MarioLevel { SMALL, BIG, FOX };

class CMario : public CMovableGameObject
{
	MarioState state;
	MarioLevel level;
	float maxVx;
	float maxVy;
	bool isGrounded;

	int lastJumpTime;

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		state = MarioState::IDLE;
		level = MarioLevel::SMALL;
		ay = MARIO_GRAVITY;
		maxVy = -MARIO_JUMP_SPEED;
		isGrounded = false;
		lastJumpTime = -1;
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

