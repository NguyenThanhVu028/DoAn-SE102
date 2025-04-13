#include "PiranhaPlant.h"
#include "debug.h"

void CPiranhaPlant::Update(DWORD dt) {
	ULONGLONG timer = GetTickCount64() - checkPoint;
	if (!hasRised) {
		if (timer > waitingTime && isActive) {
			checkPoint = GetTickCount64(); hasRised = true;
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
			y = oriY; hasRised = false; checkPoint = GetTickCount64();
		}
	}
	CGameObjectsManager::GetInstance()->CheckCollisionWith(1, 1, 0, this, dt);
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMario*>(e->obj)) {
		//DebugOutTitle(L"Timer: %f", y);
	}
};

bool CPiranhaPlant::IsRising() {
	ULONGLONG timer = GetTickCount64() - checkPoint;
	if (hasRised) {
		if (timer <= risingTime || (timer > waitingTime + risingTime && timer < waitingTime + risingTime * 2.0f)) return true;
	}
	return false;
}