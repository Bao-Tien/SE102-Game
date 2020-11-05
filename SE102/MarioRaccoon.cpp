#include "MarioRaccoon.h"
#include "Game.h"
#include "Goomba.h"

CMarioRaccoon::CMarioRaccoon(float x, float y) : CMario(x, y) {
	mType = EMarioType::RACCOON;
	
	beginFlying = 0;
}

//bool CMarioRaccoon::SwitchState(EMarioState newState)
//{
//	if(!CMario::SwitchState(newState)) return false;
//
//	switch (newState)
//	{
//	case EMarioState::FLY:
//		if (mState != EMarioState::FLY)
//		{
//			beginFlying = GetTickCount();
//			SwitchState(EMarioState::FLY);
//		}
//		if (GetTickCount() - beginFlying < 5000)
//			vy = -MARIO_JUMP_SPEED_Y * 1.25;
//		return true;
//		break;
//
//	/*case EMarioState::ATTACK:
//		return true;
//		break;*/
//	/*case KEYBOARD_PRESS_A:
//		if (!bb) ATTACK;
//		break;*/
//	}
//}

void CMarioRaccoon::KeyboardHandle(int key, bool type)
{
	CMario::KeyboardHandle(key, type);
	switch (key)
	{
	case KEYBOARD_PRESS_A:
		if (!type)
			SwitchState(EMarioState::ATTACK);
		break;
	default:
		break;
	}
}

void CMarioRaccoon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CMario::Update(dt, colliable_objects);
	
	//if (dy > 30) SwitchState(EMarioState::)
}

void CMarioRaccoon::Render()
{
	CMario::Render();
}

void CMarioRaccoon::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (mState != EMarioState::ATTACK)
	{
		left = x;
		top = y;
		right = left + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else
	{
		top = y;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;

		if (
			(GetTickCount() > beginState + timeState * 0.10 && GetTickCount() < beginState + timeState*0.28 
			|| GetTickCount() > beginState + timeState * 0.68) && nx == 1
			|| (GetTickCount() > beginState + timeState * 0.33 && GetTickCount() < beginState + timeState * 0.69) && nx == -1
			) {
			left = x - 22;
			right = left + MARIO_RACCOON_BBOX_WIDTH + 22;
		}
		else if (
			(GetTickCount() > beginState + timeState * 0.33 && GetTickCount() < beginState + timeState * 0.69) && nx == 1
			|| (GetTickCount() > beginState + timeState * 0.10 && GetTickCount() < beginState + timeState * 0.28
				|| GetTickCount() > beginState + timeState * 0.68) && nx == -1
			) {
			left = x;
			right = left + MARIO_RACCOON_BBOX_WIDTH + 22;
		}
		else {
			left = x;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			
		}
		
		
	}
}