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
	//Check collision with Tail
	if (!isKilled) {
		vector<LPGAMEOBJECT>* tempList = new vector<LPGAMEOBJECT>();
		CMario* player = dynamic_cast<CMario*>(CGameObjectsManager::GetInstance()->GetPlayer());
		(*tempList).push_back(player->GetTail());
		CCollision::GetInstance()->Process(this, dt, tempList);
	}
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!hasRised) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		e->obj->OnCollisionWith(e);
	}
	if (dynamic_cast<CKoopaTroopa*>(e->obj)) {
		OnCollisionWithShell(e);
	}
	if (dynamic_cast<CMarioTail*>(e->obj)) {
		OnCollisionWithMarioTail(e);
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
	if (dynamic_cast<CKoopaTroopa*>(e->obj)->IsHeld() || dynamic_cast<CKoopaTroopa*>(e->obj)->IsMoving()) {
		isKilled = true;
		float oX, oY;
		e->obj->GetPosition(oX, oY);
		CGameObjectsManager::GetInstance()->GetWhackEffect((x + oX) * 0.5f, (y + oY) * 0.5f);
		CGameObjectsManager::GetInstance()->GetSmokeEffect(x, y);
	}
	dynamic_cast<CKoopaTroopa*>(e->obj)->OnCollisionWithOtherEnemy(e);
}

void CPiranhaPlant::OnCollisionWithMarioTail(LPCOLLISIONEVENT e) {
	isKilled = true;
	float oX, oY;
	e->obj->GetPosition(oX, oY);
	CGameObjectsManager::GetInstance()->GetWhackEffect((x + oX) * 0.5f, (y + oY) * 0.5f);
	CGameObjectsManager::GetInstance()->GetSmokeEffect(x, y);
}