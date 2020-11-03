#include "MarioFire.h"

CMarioFire::CMarioFire(float x, float y) : CMario(x, y) {
	mType = EMarioType::FIRE;
	bullets.push_back(new CFireBullet(x, y));
	bullets.push_back(new CFireBullet(x, y));
}

void CMarioFire::SetState(int state)
{
	CMario::SetState(state);

	switch (state)
	{
	case MARIO_STATE_ATTACK:
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isHidden)
			{
				bullets[i]->isHidden = false;
				bullets[i]->x = this->x + MARIO_BIG_BBOX_WIDTH;
				bullets[i]->y = this->y + MARIO_BIG_BBOX_HEIGHT / 2;
				bullets[i]->nx = this->nx;
				return;
			}
		}
		break;
	}
}

void CMarioFire::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CMario::Update(dt, colliable_objects);
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i]->isHidden)
			{
				bullets[i]->Update(dt, colliable_objects);
			}
		}
	
}

void CMarioFire::Render()
{

		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i]->isHidden) bullets[i]->Render();
		}
	CMario::Render();
}

void CMarioFire::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;
}