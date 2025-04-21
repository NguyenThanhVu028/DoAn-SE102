#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

//struct COverlapDetail {
//	float left, top, right, bottom;
//	COverlapDetail(float left, float top, float right, float bottom) {
//		this->left = left;
//		this->top = top;
//		this->right = right;
//		this->bottom = bottom;
//	}
//};
//typedef COverlapDetail* LPOVERLAPDETAIL;

struct CCollisionEvent 
{
	LPGAMEOBJECT src_obj;		// source object : the object from which to calculate collision
	LPGAMEOBJECT obj;			// the target object

	//LPOVERLAPDETAIL overlap_detail;		//details if there is overlap
	
	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	bool isOverlap;

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, 
		LPGAMEOBJECT obj = NULL, LPGAMEOBJECT src_obj = NULL, bool isOverlap = false)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->src_obj = src_obj;
		this->isDeleted = false;
		this->isOverlap = isOverlap;
		//this->overlap_detail = overlap_detail;
	}

	int WasCollided();

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CCollision
{
	static CCollision* __instance;
public: 
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPCOLLISIONEVENT SweptAABB(
		LPGAMEOBJECT objSrc, 
		DWORD dt,
		LPGAMEOBJECT objDest); 
	void Scan(
		LPGAMEOBJECT objSrc, 
		DWORD dt, 
		vector<LPGAMEOBJECT>* objDests, 
		vector<LPCOLLISIONEVENT>& coEvents);

	void Filter(
		LPGAMEOBJECT objSrc,
		vector<LPCOLLISIONEVENT>& coEvents,
		LPCOLLISIONEVENT &colX,
		LPCOLLISIONEVENT &colY, 
		int filterBlock,		
		int filterX,
		int filterY);

	void Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects, int filter = 1, int filterX = 1, int filterY = 1);

	static CCollision* GetInstance();
};