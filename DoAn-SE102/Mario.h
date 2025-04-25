#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"
#include "MarioAniIds.h"
#include "MarioHead.h"
#include "KoopaTroopa.h"

#define MARIO_UNTOUCHABLE_TIME 2700
#define MARIO_LEVEL_LONG_TIME 800
#define MARIO_LEVEL_SHORT_TIME 400
#define MARIO_FLICKER_TIME 100
#define MARIO_DEATH_TIME 5000
#define MARIO_TURN_TIME 200
#define MARIO_KICK_SHELL_TIME 200

#define MARIO_WALK_SPEED 0.07f
#define MARIO_RUN_SPEED 0.18f
#define MARIO_RUN_MAXSPEED 0.21f
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

#define MARIO_SHELL_POSITION_OFFSET_SMALL_X 8
#define MARIO_SHELL_POSITION_OFFSET_BIG_X 10
#define MARIO_SHELL_POSITION_OFFSET_RACCOON_X 14
#define MARIO_SHELL_POSITION_OFFSET_SMALL_Y 4
#define MARIO_SHELL_POSITION_OFFSET_BIG_Y 6

enum MarioState { NONE, DIE, IDLE, SIT, JUMP, RELEASE_JUMP, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, NOT_RUN, JUMP_WALK_RIGHT, JUMP_WALK_LEFT, HOLDING };
enum MarioLevel { SMALL, BIG, RACCOON };

class CMario : public CMovableGameObject
{
	CMarioHead* head;
	CKoopaTroopa* shell;

	MarioState state;
	MarioLevel level;

	float width;
	float height;

	float maxVx;
	float maxVy;
	float maxFallSpeed;
	bool isGrounded;
	bool isRunButtonPressed;

	ULONGLONG jumpTime;
	ULONGLONG lastJumpTime;

	LONGLONG pMeter;
	LONGLONG pMeterCheckpoint;

	LPANIMATION aniToRender;

	ULONGLONG untouchable_start;
	ULONGLONG level_start;
	ULONGLONG level_duration;
	DWORD flicker_time;
	ULONGLONG death_start;
	ULONGLONG turning_start;	//Used for Mario's turning animations while holding shell
	ULONGLONG kick_shell_start;	//Used for Mario's kicking shell animations

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		auto game = CGame::GetInstance();
		state = MarioState::IDLE;
		level = MarioLevel::SMALL;
		ay = MARIO_GRAVITY;
		maxVy = -MARIO_JUMP_SPEED;
		isGrounded = false;
		lastJumpTime = -1;
		jumpTime = MARIO_JUMP_TIME;
		pMeter = 0;
		pMeterCheckpoint = game->GetTickCount();
		aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_IDLE_RIGHT);
		maxFallSpeed = -1;
		width = MARIO_BIG_BBOX_WIDTH;
		height = MARIO_SMALL_BBOX_HEIGHT;
		maxVx = 0;
		untouchable_start = game->GetTickCount() - MARIO_UNTOUCHABLE_TIME - 10;
		level_start = game->GetTickCount() - MARIO_LEVEL_LONG_TIME - 10;
		level_duration = 0;
		flicker_time = 0;
		isRunButtonPressed = false;
		turning_start = game->GetTickCount();
		head = new CMarioHead(x, y - height * 0.5f);
		head->width = width;
		shell = NULL;
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
	void OnCollisionWidthKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWidthPowerUpItem(LPCOLLISIONEVENT e);
	void OncollisionWithEnemy(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void OnLevelUp();
	void OnLevelDown();

	void OnPressRunButton() { isRunButtonPressed = true; }
	void OnReleaseRunButton();
	bool IsRunButtonPressed() { return isRunButtonPressed; }
	
	bool IsHoldingShell() { return shell != NULL; }
	void ResetTurningTimer();
	void AdjustShellPosition();
};

