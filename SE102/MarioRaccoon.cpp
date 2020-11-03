#include "MarioRaccoon.h"
#include "Game.h"

CMarioRaccoon::CMarioRaccoon(float x, float y) : CMario(x, y) {
	mType = EMarioType::RACCOON;
	
	beginFlying = 0;
}

void CMarioRaccoon::SetState(int state)
{
	CMario::SetState(state);

	switch (state)
	{
	case MARIO_STATE_FLY:
		if (!isFly)
			beginFlying = GetTickCount();
		if (GetTickCount() - beginFlying < 5000)
			vy = -MARIO_JUMP_SPEED_Y * 1.25;
		isFly = true;
		break;

	case MARIO_STATE_ATTACK:
		break;
	}
}

void CMarioRaccoon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CMario::Update(dt, colliable_objects);
	if (dy > 30) isFly = false;
}

void CMarioRaccoon::Render()
{
	CMario::Render();
}

void CMarioRaccoon::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (nx > 0)
	{
		left = x;
		top = y;
		right = left + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	if (nx < 0)
	{
		left = x;
		top = y;
		right = x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
}