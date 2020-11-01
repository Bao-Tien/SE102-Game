#include "MarioFire.h"

CMarioFire::CMarioFire(float x, float y) : CMario(x, y) {
	bullets.push_back(new CFireBullet(x, y));
	bullets.push_back(new CFireBullet(x, y));
}

void CMarioFire::SetState(int state)
{
	CMario::SetState(state);

	switch (state)
	{
	case MARIO_STATE_ATTACK:
		isAttack = true;
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isHidden)
			{
				bullets[i]->isHidden = false;
				return;
			}
		}
		break;
	}
}

void CMarioFire::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CMario::Update(dt, colliable_objects);
	if (isAttack)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i]->isHidden)
			{
				if (!bullets[i]->isInScreen()) bullets[i]->isHidden = true;
				bullets[i]->Update(dt, colliable_objects);
				bullets[i]->x = this->x + MARIO_BIG_BBOX_WIDTH;
				bullets[i]->y = this->y + MARIO_BIG_BBOX_HEIGHT / 2;
				bullets[i]->nx = this->nx;
			}
		}
	}
	
}

void CMarioFire::Render()
{
	if (vx == 0)
		ani = MARIO_ANI_FIRE_IDLE;
	else if (isRunning)
		ani = MARIO_ANI_FIRE_RUN;
	else ani = MARIO_ANI_FIRE_WALK;
	if (vy < 0)
	{
		if (isHighJump)
			ani = MARIO_ANI_FIRE_HIGH_JUMP;
		else ani = MARIO_ANI_FIRE_JUMP;
	}
	if (isAttack)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i]->isHidden) bullets[i]->Render();
		}
	}
	CMario::Render();
}

void CMarioFire::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;
}