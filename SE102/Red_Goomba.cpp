#include "Red_Goomba.h"
#include "FireBullet.h"
#include "Mario.h"

CRed_Goomba::CRed_Goomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::RED_GOOMBA;
	SetState(EnemyState::LIVE, -1.0);
}

string CRed_Goomba::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = "ani-red-goomba";
	if (eState == EnemyState::DIE) stateString = "die";
	else if (eState == EnemyState::WILL_DIE) stateString = "die";
	else if (eState == EnemyState::BEING_ATTACKED) stateString = "idle";
	else stateString = "walk";

	return typeString + "-" + stateString;
}
void CRed_Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + RED_GOOMBA_BBOX_WIDTH;
	if (eState == EnemyState::WILL_DIE)
		bottom = y + RED_GOOMBA_BBOX_HEIGHT_DIE;
	else
		if (eState == EnemyState::DIE || eState == EnemyState::BEING_ATTACKED)
			top = left = right = bottom = 0;
		else
			bottom = y + RED_GOOMBA_BBOX_HEIGHT; //live
}

void CRed_Goomba::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
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

void CRed_Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += RED_GOOMBA_GRAVITY * dt;
	CEnemy::Update(dt, coObjects);
	if (eState == EnemyState::WILL_DIE && GetTickCount() - beginState > 500)
	{
		SetState(EnemyState::DIE);
	}
}

void CRed_Goomba::SetState(EnemyState state, float nxCollision)
{
	switch (state)
	{
	case EnemyState::WILL_DIE: //bi thap xuong
		y += RED_GOOMBA_BBOX_HEIGHT - RED_GOOMBA_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		beginState = GetTickCount();
		eState = state;
		break;
	case EnemyState::BEING_ATTACKED:
		if (nxCollision < 0)
		{
			vx = RED_GOOMBA_BEING_ATTACKED_SPEED_X;
		}
		else vx = -RED_GOOMBA_BEING_ATTACKED_SPEED_X;
		vy = -RED_GOOMBA_BEING_ATTACKED_SPEED_Y;
		eState = state;
		break;
	case EnemyState::LIVE:
		vx = -RED_GOOMBA_WALKING_SPEED;
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
