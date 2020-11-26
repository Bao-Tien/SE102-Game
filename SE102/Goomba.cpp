#include "Goomba.h"
#include "FireBullet.h"
#include "Mario.h"

CGoomba::CGoomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::GOOMBA;
	SetState(EnemyState::LIVE, -1.0);
}

string CGoomba::GetAnimationIdFromState()
{
	string typeString, stateString;
	 
	typeString = "ani-goomba";
	if (eState == EnemyState::DIE) stateString = "die";
	else if (eState == EnemyState::WILL_DIE) stateString = "die";
	else if (eState == EnemyState::BEING_ATTACKED) stateString = "idle";
	else stateString = "walk";

	return typeString + "-" + stateString;
}
void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;
	if (eState == EnemyState::WILL_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 
	if (eState == EnemyState::DIE || eState == EnemyState::BEING_ATTACKED)
		top = left = right = bottom = 0;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT; //live
}

void CGoomba::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	CEnemy::CollisionX(coObj, nxCollision, Actively);
	if (Actively == 0)
	{
		if (eState != EnemyState::DIE)
		{
			CMario* mario = (CMario*)coObj;
			if (mario->mState == EMarioState::ATTACK)
				SetState(EnemyState::BEING_ATTACKED, nxCollision);
			else mario->SwitchType();
		}
		
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += GOOMBA_GRAVITY * dt;
	CEnemy::Update(dt, coObjects);
	if (eState == EnemyState::WILL_DIE && GetTickCount() - beginState > 400)
	{
		SetState(EnemyState::DIE);
	}
	//DebugOut(ToWSTR("------->" + std::to_string(vx) + "\n" ).c_str());
}

void CGoomba::SetState(EnemyState state, float nxCollision)
{
	switch (state)
	{
	case EnemyState::WILL_DIE: //bi thap xuong
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		beginState = GetTickCount();
		eState = state;
		break;
	case EnemyState::BEING_ATTACKED:
		if (nxCollision < 0)
		{
			vx = GOOMBA_BEING_ATTACKED_SPEED_X;
		}
		else vx = -GOOMBA_BEING_ATTACKED_SPEED_X;
		vy = -GOOMBA_BEING_ATTACKED_SPEED_Y;
		eState = state;
		break;
	case EnemyState::LIVE:
		vx = -GOOMBA_WALKING_SPEED;
		eState = state;
		break;
	case EnemyState::DIE:
		vx = 0;
		vy = 0;
		this->isHidden = true; // roi ma tai sao van renden goomba bi roi xuong
		eState = state;
		break;
	}
}
