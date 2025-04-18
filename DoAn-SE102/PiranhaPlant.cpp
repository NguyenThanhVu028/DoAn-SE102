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
	if (dynamic_cast<CMario*>(e->obj)) {
		//DebugOutTitle(L"Timer: %f", y);
	}
};

bool CPiranhaPlant::IsRising() {
	ULONGLONG timer = CGame::GetInstance()->GetTickCount() - checkPoint;
	if (hasRised) {
		if (timer <= risingTime || (timer > waitingTime + risingTime && timer < waitingTime + risingTime * 2.0f)) return true;
	}
	return false;
}