#include "MarioFire.h"

CMarioFire::CMarioFire(float x, float y) : CMario(x, y) {
	mType = EMarioType::FIRE;
	bullets.push_back(new CFireBullet(x, y));
	bullets.push_back(new CFireBullet(x, y));
}

//bool CMarioFire::SwitchState(EMarioState newState)
//{
//	if(!CMario::SwitchState(newState)) return false;
//
//	switch (newState)
//	{
//	case EMarioState::ATTACK:
//		for (int i = 0; i < bullets.size(); i++)
//		{
//			if (bullets[i]->isHidden)
//			{
//				bullets[i]->isHidden = false;
//				bullets[i]->x = this->x + MARIO_BIG_BBOX_WIDTH;
//				bullets[i]->y = this->y + MARIO_BIG_BBOX_HEIGHT / 2;
//				bullets[i]->nx = this->nx;
//				return true;
//			}
//		}
//		break;
//	}
//}
void CMarioFire::KeyboardHandle(int key, bool type)
{
	CMario::KeyboardHandle(key, type);
	switch (key)
	{
	case KEYBOARD_PRESS_A:
		if (!type) {
			SwitchState(EMarioState::ATTACK);
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