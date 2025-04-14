#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"

#define MARIO_WALKING_SPEED 0.07f
#define MARIO_RUNNING_SPEED 0.2f
#define MARIO_RUNNING_MAXSPEED 0.25f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_WALKING_ACCEL_X 0.000125f
#define MARIO_RUNNING_ACCEL_X 0.000125f

#define MARIO_DECEL_X 0.00015f
#define MARIO_BRAKE_DECEL MARIO_DECEL_X * 2.5f

#define MARIO_JUMP_TIME 220
#define MARIO_JUMP_WALK_TIME 250
#define MARIO_JUMP_RUN_TIME 275
#define MARIO_JUMP_RUN_MAXSPEED_TIME 300
#define MARIO_JUMP_SPEED 0.22f
//#define MARIO_JUMP_RUN_SPEED 0.0.25f
//#define MARIO_JUMP_RUN_MAXSPEED 0.27f
#define MARIO_JUMP_ACCEL 0.001f

#define MARIO_GRAVITY 0.0008f

#define MARIO_JUMP_DEFLECT_SPEED 0.4f

#define MARIO_PMETER_MAX 1500

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

//Animations ID
#define MARIO_SMALL_ANIMATION_IDLE_RIGHT 10011
#define MARIO_SMALL_ANIMATION_IDLE_LEFT 10012
#define MARIO_SMALL_ANIMATION_DIE 10031
#define MARIO_SMALL_ANIMATION_JUMP_RIGHT 10021
#define MARIO_SMALL_ANIMATION_JUMP_LEFT 10022
#define MARIO_SMALL_ANIMATION_WALK_RIGHT 10041
#define MARIO_SMALL_ANIMATION_WALK_LEFT 10051
#define MARIO_SMALL_ANIMATION_BRAKE_RIGHT 10061
#define MARIO_SMALL_ANIMATION_BRAKE_LEFT 10062
#define MARIO_SMALL_ANIMATION_RUN_RIGHT 10071
#define MARIO_SMALL_ANIMATION_RUN_LEFT 10081
#define MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_RIGHT 10091
#define MARIO_SMALL_ANIMATION_JUMP_MAXSPEED_LEFT 10092
#define MARIO_SMALL_ANIMATION_RUN_MAXSPEED_RIGHT 10101
#define MARIO_SMALL_ANIMATION_RUN_MAXSPEED_LEFT	10111

enum MarioState { DIE, IDLE, SIT, JUMP, RELEASE_JUMP, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, NOT_RUN, JUMP_WALK_RIGHT, JUMP_WALK_LEFT };
enum MarioLevel { SMALL, BIG, RACCOON };

class CMario : public CMovableGameObject
{
	MarioState state;
	MarioLevel level;
	float maxVx;
	float maxVy;
	bool isGrounded;

	ULONGLONG jumpTime;
	ULONGLONG lastJumpTime;

	LONGLONG pMeter;
	LONGLONG pMeterCheckpoint;

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		state = MarioState::IDLE;
		level = MarioLevel::SMALL;
		ay = MARIO_GRAVITY;
		maxVy = -MARIO_JUMP_SPEED;
		isGrounded = false;
		lastJumpTime = -1;
		jumpTime = MARIO_JUMP_TIME;
		pMeter = 0;
		pMeterCheckpoint = GetTickCount64();
		//vy = -0.1f;
	}

	void Update(DWORD dt);
	void Render();

	int GetAnimationSMALL();
	int GetAnimationBIG();
	int GetAnimationFOX();

	void SetState(MarioState state);
	MarioState GetState() { return state; }

	void SetLevel(MarioLevel level) { this->level = level; }
	MarioLevel GetLevel() { return level; }

	int IsCollidable() { return state != MarioState::DIE; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWidthPowerUpItem(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

