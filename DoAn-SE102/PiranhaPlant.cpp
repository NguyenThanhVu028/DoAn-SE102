#include "PiranhaPlant.h"
#include "debug.h"

void CPiranhaPlant::Update(DWORD dt) {
	ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
	if (!hasRised) {
		if (timer > waitingTime && isActive) {
			checkPoint = CGame::GetInstance()->GetTickCount(); hasRised = true;
		}
		else return;
	}
	else {
		if (timer <= risingTime) {
			y = oriY - risingHeight * ((1.0f * timer / risingTime));
		}
		else if(timer < waitingTime + risingTime){
			y = oriY - risingHeight;
		}
		else if(timer < waitingTime + risingTime * 2.0f){
			y = oriY - risingHeight * (1.0f - ((1.0f * timer - (waitingTime + risingTime)) / risingTime));
		}
		else {
			y = oriY; hasRised = false; checkPoint = CGame::GetInstance()->GetTickCount();
		}
	}
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 1, 1, 0);
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!hasRised) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		e->obj->OnCollisionWith(e);
	}
	if (dynamic_cast<CKoopaTroopa*>(e->obj)) {
		OnCollisionWithShell(e);
	}
};

bool CPiranhaPlant::IsRising() {
	ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
	if (hasRised) {
		if (timer <= risingTime || (timer > waitingTime + risingTime && timer < waitingTime + risingTime * 2.0f)) return true;
	}
	return false;
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_PLANT_WIDTH * 0.5f;
	top = y - PIRANHA_PLANT_HEIGHT * 0.5f;
	right = x + PIRANHA_PLANT_WIDTH * 0.5f;
	bottom = y + PIRANHA_PLANT_HEIGHT * 0.5f;
}

bool CPiranhaPlant::IsDead()
{
	return false;
}

void CPiranhaPlant::OnCollisionWithShell(LPCOLLISIONEVENT e) {
	if(dynamic_cast<CKoopaTroopa*>(e->obj)->IsHeld() || dynamic_cast<CKoopaTroopa*>(e->obj)->IsMoving())
		isKilled = true;
	dynamic_cast<CKoopaTroopa*>(e->obj)->OnCollisionWithOtherEnemy(e);
}
