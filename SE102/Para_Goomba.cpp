#include "Para_Goomba.h"
#include "Mario.h"

CPara_Goomba::CPara_Goomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::PARA_GOOMBA;
	SetState(EnemyState::LIVE, -1.0);
	remember = 3;
	count = 0;
}
string CPara_Goomba::GetAnimationIdFromState()
{
	string typeString, stateString;
	typeString = "ani-red-para-goomba";
	if (eState == EnemyState::LIVE) stateString = "idle";
	else stateString = "fly";
	return typeString + "-" + stateString;
}

void CPara_Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PARA_BBOX_WIDTH;
	if (eState == EnemyState::WILL_DIE)
		top = left = right = bottom = 0;
	else if(eState == EnemyState::LIVE)
		bottom = y + PARA_BBOX_HEIGHT;
	else 
		bottom = y + PARA_BBOX_FLY_HEIGHT;
}

void CPara_Goomba::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	CEnemy::CollisionX(coObj, nxCollision, Actively);
	if (Actively == 0)
	{
		if (eState != EnemyState::DIE)
		{
			CMario* mario = (CMario*)coObj;
			mario->SwitchType(1);
		}
	}
}

void CPara_Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += PARA_GRAVITY * dt;
	CEnemy::Update(dt, coObjects);
	if (eState == EnemyState::LIVE && GetTickCount() - beginState > 1000)
	{
		SetState(EnemyState::JUMP);
		y += PARA_BBOX_HEIGHT - PARA_BBOX_FLY_HEIGHT -10;
		count++;
	}
	if (eState == EnemyState::JUMP)
	{
		if (count < remember)
		{
			SetState(EnemyState::JUMP);
			count++;
		}
		else count = 0;
	}

}

void CPara_Goomba::SetState(EnemyState state, float nxCollision)
{//di 3 buoc(live), nhay 3 buoc nho(jump), nhay 1 buoc lon (hight_jump)
	switch (state)
	{
	case EnemyState::WILL_DIE: //chuan bi chuyen red_goomba
		vx = 0;
		vy = 0;
		this->isHidden = true;
		eState = state;
		break;
	case EnemyState::HIGHT_JUMP:
		vy = -PARA_HIGHT_JUMP_SPEED_Y;
		eState = state;
		break;
	case EnemyState::JUMP:
		vy = -PARA_JUMP_SPEED_Y;
		eState = state;
		break;
	case EnemyState::LIVE:
		vx = -PARA_WALKING_SPEED;
		beginState = GetTickCount();
		eState = state;
		break;
	}
}