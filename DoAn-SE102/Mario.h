#pragma once
#include <algorithm>
#include "MovableGameObject.h"
#include "GameObjectsManager.h"
#include "debug.h"
#include "MarioAniIds.h"
#include "MarioHead.h"
#include "MarioTail.h"
#include "KoopaTroopa.h"

#define MARIO_UNTOUCHABLE_TIME 2700
#define MARIO_LEVEL_LONG_TIME 800
#define MARIO_LEVEL_SHORT_TIME 400
#define MARIO_FLICKER_TIME 100
#define MARIO_DEATH_TIME 5000
#define MARIO_TURN_TIME 200
#define MARIO_KICK_SHELL_TIME 200
#define MARIO_SPIN_TIME 225
#define MARIO_SLOW_FALLING_TIME 300
#define MARIO_FLY_TIME 175

#define MARIO_WALK_SPEED 0.075f
#define MARIO_RUN_SPEED 0.15f
#define MARIO_RUN_MAXSPEED 0.2f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_WALK_ACCEL_X 0.0002f
#define MARIO_RUN_ACCEL_X 0.000055f

#define MARIO_DECEL_X 0.00015f
#define MARIO_BRAKE_DECEL MARIO_DECEL_X * 2.5f

#define MARIO_JUMP_TIME 270
#define MARIO_MIN_JUMP_TIME 100
#define MARIO_JUMP_WALK_TIME 280
#define MARIO_JUMP_RUN_TIME 295
#define MARIO_JUMP_RUN_MAXSPEED_TIME 300
#define MARIO_JUMP_SPEED 0.22f
//#define MARIO_JUMP_MIN_SPEED 0.1f
#define MARIO_JUMP_ACCEL 0.0025f

#define MARIO_FLY_SPEED MARIO_JUMP_SPEED * 0.4f

#define MARIO_GRAVITY 0.0012f
#define MARIO_FALL_SPEED 0.4f
#define MARIO_SLOW_FAlL_SPEED 0.05f

#define MARIO_JUMP_DEFLECT_SPEED 0.4f

#define MARIO_PMETER_MAX 100
#define MARIO_PMETER_DECREASE_SPEED 0.025f
#define MARIO_PMETER_TIME 5000

#define MARIO_SMALL_BBOX_WIDTH  14
#define MARIO_SMALL_BBOX_HEIGHT 12
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SHELL_POSITION_OFFSET_SMALL_X 8
#define MARIO_SHELL_POSITION_OFFSET_BIG_X 10
#define MARIO_SHELL_POSITION_OFFSET_RACCOON_X 10
#define MARIO_SHELL_POSITION_OFFSET_SMALL_Y 4
#define MARIO_SHELL_POSITION_OFFSET_BIG_Y 6

#define MARIO_TAIL_POSITION_OFFSET_X 11
#define MARIO_TAIL_POSITION_OFFSET_Y 7

enum MarioState { NONE, DIE, IDLE, SIT, JUMP, RELEASE_JUMP, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, NOT_RUN, JUMP_WALK_RIGHT, JUMP_WALK_LEFT, HOLDING, SPIN };
enum MarioLevel { SMALL, BIG, RACCOON };

class CMario : public CMovableGameObject
{
	CMarioHead* head;
	CMarioTail* tail;
	CKoopaTroopa* shell;
	CGameObject* enterablePipe;

	MarioState state;
	MarioLevel level;

	float width;
	float height;

	float targetVx;
	float maxVy;
	float maxFallSpeed;
	bool isGrounded;
	bool isRunButtonPressed;

	ULONGLONG jumpTime;
	ULONGLONG lastJumpTime;

	float pMeter;
	bool isPMeterMax;

	int isSpinning;
	bool isNeedResetAni;

	bool isHidden;

	int streak;

	LPANIMATION aniToRender;

	ULONGLONG untouchable_start;
	ULONGLONG level_start;
	ULONGLONG level_duration;
	DWORD flicker_time;
	ULONGLONG death_start;
	ULONGLONG turning_start;	//Used for Mario's turning animations while holding shell
	ULONGLONG kick_shell_start;	//Used for Mario's kicking shell animations
	ULONGLONG pMeterMax_start;	//Used for Mario's raccoon form when pMeter is at maximum
	ULONGLONG spin_start;
	ULONGLONG slowFalling_start;
	ULONGLONG fly_start;

public:

	CMario(float x, float y) : CMovableGameObject(x, y) {
		auto game = CGame::GetInstance();

		//Basic properties
		state = MarioState::IDLE;
		level = MarioLevel::SMALL;
		width = MARIO_BIG_BBOX_WIDTH;
		height = MARIO_SMALL_BBOX_HEIGHT;
		isHidden = false;
		streak = 1;

		//Velocity
		targetVx = 0;					//Mario target velocity, the game will calculate acceleration based on target velocity and current velocity
		ay = MARIO_GRAVITY;
		maxVy = -MARIO_JUMP_SPEED;
		maxFallSpeed = MARIO_FALL_SPEED;
		
		//Actions
		isGrounded = false;
		lastJumpTime = game->GetTickCount() - MARIO_JUMP_TIME - 10;
		jumpTime = MARIO_JUMP_TIME;
		isSpinning = 0;
		level_duration = 0;
		isRunButtonPressed = false;

		//PMeter
		pMeter = 0;
		isPMeterMax = false;

		//Aniamtions
		aniToRender = CAnimations::GetInstance()->Get(MARIO_SMALL_ANIMATION_IDLE_RIGHT);
		flicker_time = 0;
		isNeedResetAni = false;
		
		//Mario's body parts
		head = new CMarioHead(x, y - height * 0.5f);
		tail = new CMarioTail(x, y);
		head->width = width;
		shell = NULL;
		enterablePipe = NULL;

		//Timer
		untouchable_start = game->GetTickCount() - MARIO_UNTOUCHABLE_TIME - 10;
		level_start = game->GetTickCount() - MARIO_LEVEL_LONG_TIME - 10;
		death_start = game->GetTickCount() - MARIO_DEATH_TIME - 10;
		fly_start = game->GetTickCount() - MARIO_FLY_TIME - 10;
		kick_shell_start = game->GetTickCount() - MARIO_KICK_SHELL_TIME - 10;
		pMeterMax_start = game->GetTickCount() - MARIO_PMETER_TIME - 10;
		slowFalling_start = game->GetTickCount() - MARIO_SLOW_FALLING_TIME;
		spin_start = game->GetTickCount() - MARIO_SPIN_TIME;
		turning_start = game->GetTickCount() - MARIO_TURN_TIME - 10;
	}

	void Update(DWORD dt);
	void Render();

	void GetAnimationSMALL();
	void GetAnimationBIG();
	void GetAnimationRACCOON();

	void SetState(MarioState state);
	MarioState GetState() { return state; }

	void SetLevel(MarioLevel level) { this->level = level; CGame::GetInstance()->SetMarioLevel(level); }
	MarioLevel GetLevel() { return level; }

	float GetPMeter() { return pMeter; }
	bool IsPMeterMax() { return isPMeterMax; }

	int IsCollidable() { return state != MarioState::DIE; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWidthKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWidthPowerUpItem(LPCOLLISIONEVENT e);
	void OncollisionWithEnemy(LPCOLLISIONEVENT e);
	void OnCollisionWithFinalReward(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void OnLevelUp();
	void OnLevelDown();

	void OnPressRunButton() { isRunButtonPressed = true; }
	void OnReleaseRunButton();
	bool IsRunButtonPressed() { return isRunButtonPressed; }

	void EnterPipe();
	
	bool IsHoldingShell() { return shell != NULL; }
	void ResetTurningTimer();
	void AdjustShellPosition();

	CMarioTail* GetTail() { return tail; }
	
	void CheckHeadCollision(DWORD dt);
	void CheckTailCollision(DWORD dt);
	void UpdatePMeter(DWORD dt);
	void UpdateVelocity(DWORD dt);

	void Hide() { isHidden = true; }
	void UnHide() { isHidden = false; }

	void EnterPipe(bool direction);
};

