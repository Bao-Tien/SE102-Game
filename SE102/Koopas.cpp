#include "Koopas.h"
#include "ScenceManager.h"
#include "Game.h"
#include "Mario.h"
#include "MarioConst.h"
#include "PlayScence.h"

CKoopas::CKoopas(float x, float y) : CEnemy(x, y)
{
	SetState(EnemyState::LIVE, -1.0);
	beginState = 0;
}

string CKoopas::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = "ani-red-koopa-troopa";
	if (eState == EnemyState::LIVE ) stateString = "move";
	else if (eState == EnemyState::WILL_DIE || eState == EnemyState::DIE || eState == EnemyState::BEING_HELD 
		|| eState == EnemyState::BEING_ATTACKED || eState == EnemyState::BEING_KICK)
		stateString = "crouch";

	return typeString + "-" + stateString;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (eState == EnemyState::WILL_DIE || eState == EnemyState::BEING_HELD || eState == EnemyState::BEING_KICK)
		bottom = y + KOOPAS_BBOX_HEIGHT_COUCH;
	else if (eState == EnemyState::BEING_ATTACKED || eState == EnemyState::DIE)
		left = top = right = bottom = 0;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	CEnemy::CollisionX(coObj, nxCollision, Actively);
	if (Actively==0)
	{
		CMario* mario = (CMario*)coObj;
		if (eState != EnemyState::DIE)
		{
			if (mario->mState == EMarioState::ATTACK)
			{
				SetState(EnemyState::BEING_ATTACKED, nxCollision); //quay duoi//ban
			}
			else if (mario->vxMax == VELOCITY_X_SPEEDUP_MAX) //nhan nut A
			{
				if (eState == EnemyState::WILL_DIE)
				{
					mario->SwitchState(EMarioState::HOLD);
					SetState(EnemyState::WILL_DIE, nxCollision); //cam
				}
			}
			else if (mario->mState == EMarioState::WALK)
			{
				if (eState != EnemyState::LIVE)
				{
					SetState(EnemyState::BEING_KICK, nxCollision);//bi da
				}
				else mario->SwitchType(1);
			}
			else mario->SwitchType(1);
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += KOOPAS_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	
	if (eState== EnemyState::WILL_DIE && GetTickCount() - beginState > 5000)
	{
		SetState(EnemyState::LIVE);
		y += KOOPAS_BBOX_HEIGHT_COUCH - KOOPAS_BBOX_HEIGHT;
	}
	
	if (eState == EnemyState::WILL_DIE)
	{
		LPGAMEOBJECT player = CScences::GetInstance()->Get(CGame::GetInstance()->GetCurrentSceneId())->GetPlayer();
		if (player->GetvxMax() == VELOCITY_X_SPEEDUP_MAX) { //nhan A //bi cam
			float l, t, r, b;
			player->GetBoundingBox(l, t, r, b);
			int nxPlayer = player->nx;
			if (nxPlayer == 1)
				x = player->x + (r - l);
			else
				x = player->x - KOOPAS_BBOX_WIDTH;
			y = (player->y + KOOPAS_BBOX_HEIGHT_COUCH / 3);
		}
		/*else
			SetState(EnemyState::DIE);*/
	}	
}

void CKoopas::SetState(EnemyState state, float nxCollision)
{
	switch (state)
	{
	case EnemyState::WILL_DIE: //nhay len dau 
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_COUCH;
		vx = 0;
		vy = 0;
		beginState = GetTickCount();
		eState = state;
		break;
	case EnemyState::LIVE:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		eState = state;
		break;
	case EnemyState::BEING_ATTACKED: // bi quay duoi // bi ban
		if (nxCollision < 0)
		{
			vx = KOOPAS_BEING_ATTACKED_SPEED_X;
		}
		else vx = -KOOPAS_BEING_ATTACKED_SPEED_X;
		vy = -KOOPAS_BEING_ATTACKED_SPEED_Y;
		eState = state;
		break;
	case EnemyState::BEING_KICK: //da
		if (nxCollision > 0)
			vx = -KOOPAS_BEING_KICK_SPEED
		else vx = KOOPAS_BEING_KICK_SPEED;
		eState = state;
		break;
	case EnemyState::BEING_HELD:
		eState = state;
		break;
	case EnemyState::DIE:
		vx = 0;
		vy = 0;
		eState = state;
		break;
	}

}