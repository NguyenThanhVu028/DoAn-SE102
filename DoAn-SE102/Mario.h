#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"
#include "MarioAniIds.h"

#define MARIO_WALK_SPEED 0.07f
#define MARIO_RUN_SPEED 0.2f
#define MARIO_RUN_MAXSPEED 0.25f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_WALK_ACCEL_X 0.000125f
#define MARIO_RUN_ACCEL_X 0.000125f

#define MARIO_DECEL_X 0.00015f
#define MARIO_BRAKE_DECEL MARIO_DECEL_X * 2.5f

#define MARIO_JUMP_TIME 220
#define MARIO_JUMP_WALK_TIME 250
#define MARIO_JUMP_RUN_TIME 275
#define MARIO_JUMP_RUN_MAXSPEED_TIME 300
#define MARIO_JUMP_SPEED 0.22f
#define MARIO_JUMP_ACCEL 0.001f

#define MARIO_GRAVITY 0.001f
#define MARIO_MAX_FAlL_SPEED 0.1f

#define MARIO_JUMP_DEFLECT_SPEED 0.4f

#define MARIO_PMETER_MAX 1500

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

enum MarioState { NONE, DIE, IDLE, SIT, JUMP, RELEASE_JUMP, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, NOT_RUN, JUMP_WALK_RIGHT, JUMP_WALK_LEFT, HOLDING };
enum MarioLevel { SMALL, BIG, RACCOON };

class CMario : public CMovableGameObject
{
	MarioState state;
	MarioLevel level;

	int width;
	int height;

	float maxVx;
	float maxVy;
	float maxFallSpeed;
	bool isGrounded;
	//float slowFalling;

	ULONGLONG jumpTime;
	ULONGLONG lastJumpTime;

	LONGLONG pMeter;
	LONGLONG pMeterCheckpoint;

	LPANIMATION aniToRender;

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		state = MarioState::IDLE;
		level = MarioLevel::BIG;
		ay = MARIO_GRAVITY;
		maxVy = -MARIO_JUMP_SPEED;
		isGrounded = false;
		lastJumpTime = -1;
		jumpTime = MARIO_JUMP_TIME;
		pMeter = 0;
		pMeterCheckpoint = CGame::GetInstance()->GetTickCount();
		aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_IDLE_RIGHT);
		maxFallSpeed = -1;
		width = MARIO_BIG_BBOX_WIDTH;
		height = MARIO_BIG_BBOX_HEIGHT;
	}

	void Update(DWORD dt);
	void Render();

	void GetAnimationSMALL();
	void GetAnimationBIG();
	void GetAnimationRACCOON();

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

	void OnLevelUp();
	void OnLevelDown();
};

