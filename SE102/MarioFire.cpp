#include "MarioFire.h"
#define DELTA_X_FIRE_BULLET		20
CMarioFire::CMarioFire(float x, float y) : CMario(x, y) {
	mType = EMarioType::FIRE;
	bullets.push_back(new CFireBullet(1, x, y));
	bullets.push_back(new CFireBullet(1, x, y));
}

void CMarioFire::KeyboardHandle(int key, bool type)
{
	CMario::KeyboardHandle(key, type);
	switch (key)
	{
	case KEYBOARD_PRESS_A:
		if (!type) {
			for (int i = 0; i < bullets.size(); i++)
			{
				if (bullets[i]->isHidden)
				{
					SwitchState(EMarioState::ATTACK, 300);
					//bullets[i]->x = this->x + MARIO_BIG_BBOX_WIDTH + ((nx == 1) ? -DELTA_X_FIRE_BULLET : -DELTA_X_FIRE_BULLET*2);
					bullets[i]->x = (nx == 1) ? (this->x + MARIO_BIG_BBOX_WIDTH) : this->x;
					bullets[i]->y = this->y + MARIO_BIG_BBOX_HEIGHT / 2 - DELTA_X_FIRE_BULLET;
					bullets[i]->SetState(BULLET_STATE_ACTIVE, this->nx);
					return;
				}
			}
		}
			
		break;
	default:
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