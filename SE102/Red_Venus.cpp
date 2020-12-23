#include "Red_Venus.h"
#include "Mario.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Game.h"
#include "GameObject.h"

CRed_Venus::CRed_Venus(float x, float y) : CEnemy(x,y)
{
	eType = EnemyType::RED_VENUS;
	yStart = y;
	SetState(EnemyState::UP, GetnxFromMario());
}

string CRed_Venus::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = "ani-red-venus-fire-trap";
	if (eState == EnemyState::UP || eState == EnemyState::DOWN) stateString = "headup";
	else if (eState == EnemyState::ATTACK) stateString = "headdown-idle";
	else stateString = "headup";

	return typeString + "-" + stateString;
}

void CRed_Venus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + VENUS_BBOX_WIDTH;
	bottom = y + VENUS_BBOX_HEIGHT;
}

void CRed_Venus::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (Actively == 0)
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(1);
	}
}
void CRed_Venus::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 0)
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(1);
	}
}

void CRed_Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);
	if (eState == EnemyState::UP)
	{
		if (y > yStart - VENUS_BBOX_HEIGHT)
		{
			y -= 3;
		}
		else SetState(EnemyState::ATTACK);
	}
	if (eState == EnemyState::ATTACK && GetTickCount() - beginState > 1000)
	{
		SetState(EnemyState::DOWN);
	}
	if (eState == EnemyState::DOWN)
	{
		if (y < yStart)
		{
			y += 3;
		}
		else SetState(EnemyState::UP);
	}
}

void CRed_Venus::SetState(EnemyState state, float nxCollision)
{
	switch (state)
	{
	case EnemyState::UP:
		eState = state;
		break;
	case EnemyState::DOWN:
		eState = state;
		break;
	case EnemyState::ATTACK:
		beginState = GetTickCount();
		eState = state;
		break;
	default:
		break;
	}
}

int CRed_Venus::GetnxFromMario()
{
	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
	CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
	LPGAMEOBJECT obj = s->GetPlayer();
	CMario* mario = (CMario*)obj;
	if (mario->GetX() < this->x + VENUS_BBOX_WIDTH)
		return nx = -1;
	return nx = 1;
}