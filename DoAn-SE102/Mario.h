#pragma once
#include "MovableGameObject.h"

#define MARIO_WALKING_SPEED 0,1f
#define MARIO_RUNNING_SPEED 0,2f

#define MARIO_WALKING_ACCEL_X 0.0005f
#define MARIO_RUNNING_ACCEL_X 0.0007f

#define MARIO_JUMP_SPEED 0.5f
#define MARIO_JUMP_RUN_SPEED 0.6f

#define MARIO_GRAVITY 0.002f

class CMario : public MovableGameObject
{
};

