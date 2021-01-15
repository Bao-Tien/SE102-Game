#include "MarioRaccoon.h"
#include "Game.h"
#include "Goomba.h"

CMarioRaccoon::CMarioRaccoon(float x, float y) : CMario(x, y) {
	mType = EMarioType::RACCOON;
	
	beginFlying = 0;
}


void CMarioRaccoon::KeyboardHandle(int key, bool type)
{
	CMario::KeyboardHandle(key, type);

	switch (key)
	{
	case KEYBOARD_PRESS_A:
		if (!type)
			if (SwitchState(EMarioState::ATTACK, 400)) {
				hasAttack = false;
			}
		break;
	case KEYBOARD_PRESS_S:
		if (!type) 
		{
			if (synergies > 600) {
				if (mState != EMarioState::JUMP)
				{
					vy = -MARIO_FLY_SPEED_Y;
				}
				
				SwitchState(EMarioState::FLY, 900);
				
			}
				
			SwitchState(EMarioState::FALL_SLIGHTLY, 150);
					
		}
		break;
	default:
		break;
	}
}

void CMarioRaccoon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CMario::Update(dt, colliable_objects);
}

void CMarioRaccoon::Render()
{
	CMario::Render();
}

void CMarioRaccoon::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (mState != EMarioState::ATTACK || hasAttack == true)
	{
		left = x;
		top = y;
		right = left + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else
	{
		top = y + MARIO_RACCOON_BBOX_HEIGHT * 0.65f;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
		left = x - 20;
		right = left + MARIO_RACCOON_BBOX_WIDTH + 44;
		
	}
}