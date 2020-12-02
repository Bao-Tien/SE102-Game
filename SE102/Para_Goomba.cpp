#include "Para_Goomba.h"
#include "FireBullet.h"
#include "Mario.h"

CPara_Goomba::CPara_Goomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::PARA_GOOMBA;
	SetState(EnemyState::LIVE, -1.0);
}

string CPara_Goomba::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = "ani-red-goomba";
	if (eState == EnemyState::DIE) stateString = "die";
	else if (eState == EnemyState::WILL_DIE) stateString = "die";
	else if (eState == EnemyState::BEING_ATTACKED) stateString = "idle";
	else stateString = "walk";

	return typeString + "-" + stateString;
}
void CPara_Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PARA_BBOX_WIDTH;
	if (eState == EnemyState::WILL_DIE)
		bottom = y + PARA_BBOX_HEIGHT_COUCH;
	else
		if (eState == EnemyState::DIE || eState == EnemyState::BEING_ATTACKED)
			top = left = right = bottom = 0;
		else
			bottom = y + PARA_BBOX_HEIGHT; //live
}

void CPara_Goomba::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	CEnemy::CollisionX(coObj, nxCollision, Actively);
	if (Actively == 0)
	{
		if (eState != EnemyState::DIE)
		{
			CMario* mario = (CMario*)coObj;
			if (mario->mState == EMarioState::ATTACK)
				SetState(EnemyState::BEING_ATTACKED, nxCollision);
			else mario->SwitchType(1);
		}

	}
}

void CPara_Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += PARA_GRAVITY * dt;
	CEnemy::Update(dt, coObjects);
	if (eState == EnemyState::WILL_DIE && GetTickCount() - beginState > 4000)
	{
		SetState(EnemyState::DIE);
	}
	DebugOut(ToWSTR("------->a" + std::to_string(y) + "\n").c_str());
	if (vy > 0)
		DebugOut(ToWSTR("------->" + std::to_string(vy) + "\n").c_str());
}

void CPara_Goomba::SetState(EnemyState state, float nxCollision)
{
	switch (state)
	{
	case EnemyState::WILL_DIE: //bi thap xuong
		y += PARA_BBOX_HEIGHT - PARA_BBOX_HEIGHT_COUCH;
		vx = 0;
		vy = 0;
		beginState = GetTickCount();
		eState = state;
		break;
	case EnemyState::BEING_ATTACKED:
		if (nxCollision < 0)
		{
			vx = PARA_BEING_ATTACKED_SPEED_X;
		}
		else vx = -PARA_BEING_ATTACKED_SPEED_X;
		vy = -PARA_BEING_ATTACKED_SPEED_Y;
		eState = state;
		break;
	case EnemyState::LIVE:
		vx = -PARA_WALKING_SPEED;
		eState = state;
		break;
	case EnemyState::DIE:
		vx = 0;
		vy = 0;
		this->isHidden = true;
		eState = state;
		break;
	}
}