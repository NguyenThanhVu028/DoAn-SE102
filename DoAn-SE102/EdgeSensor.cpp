#include "EdgeSensor.h"
#include "GameObjectsManager.h"

void CEdgeSensor::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width * 0.5f;
	top = y - height * 0.5f;
	right = x + width * 0.5f;
	bottom = y + height * 0.5f;
}

void CEdgeSensor::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny < 0) {
		LPCOLLISIONEVENT newEvent = new CCollisionEvent(0, 0, 0);
		*newEvent = *e;
		touchedBlocks.push_back(newEvent);
	}
}

void CEdgeSensor::ClearTouchedBlocks() {
	for (auto i : touchedBlocks) delete i;
	touchedBlocks.clear();
}
void CEdgeSensor::ProcessTouchedBlocks() {
	rightEdge = leftEdge = false;
	if (touchedBlocks.size() == 0) {
		rightEdge = leftEdge = true;
		return;
	}
	for (auto i : touchedBlocks) {
		float oL, oT, oR, oB;
		i->obj->GetBoundingBox(oL, oT, oR, oB);
		if (oL <= x - width * 0.5f) leftEdge = true;
		if (oR >= x + width * 0.5f) rightEdge = true;
	}
}

void CEdgeSensor::ProcessCollision(DWORD dt) {
	ClearTouchedBlocks();
	CGameObjectsManager::GetInstance()->CheckCollisionWith(this, dt, 0, 0, 1, 0, -1);
	ProcessTouchedBlocks();
}