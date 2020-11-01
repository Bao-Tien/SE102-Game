#include "MarioRaccoon.h"
#include "Game.h"

CMarioRaccoon::CMarioRaccoon(float x, float y) : CMario(x, y) {

}

void CMarioRaccoon::SetState(int state)
{
	CMario::SetState(state);

	switch (state)
	{
	case MARIO_STATE_FLY:
		/*while (this->y < CGame::GetInstance()->camera->GetCamPosition().y + 50)
			vy += MARIO_GRAVITY * dt;*/
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
	if (vx == 0)
		ani = MARIO_ANI_RACCOON_IDLE;
	else if (isRunning)
		ani = MARIO_ANI_RACCOON_RUN;
	else ani = MARIO_ANI_RACCOON_WALK;
	if (vy < 0)
	{
		ani = MARIO_ANI_RACCOON_JUM;
	}
	if (isAttack)
	{
		ani = MARIO_ANI_RACCOON_ATTACK;
	}
	if (isFly)
	{
		ani = MARIO_ANI_RACCOON_FLY;
		
	}
	CMario::Render();
}

void CMarioRaccoon::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_RACCOON_BBOX_WIDTH;
	bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
}