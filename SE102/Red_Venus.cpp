#include "Red_Venus.h"
#include "Mario.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Game.h"
#include "GameObject.h"

CRed_Venus::CRed_Venus(float x, float y) : CEnemy(x,y)
{
	eGravity = 0;
	eType = EnemyType::RED_VENUS;
	yStart = y +3;
	SetState(EnemyState::IDLE_DOWN, VENUS_RED_TIME_IDLE_DOWN);
	bullet = new CBullet_Venus(x, y);
}

string CRed_Venus::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = VENUS_RED_ANI;
	if (eState == EnemyState::GOING_UP || eState == EnemyState::GOING_DOWN) stateString = HEADUP_ANI;
	else if (eState == EnemyState::IDLE_UP || eState == EnemyState::IDLE_DOWN || eState == EnemyState::ATTACK) stateString = HEADDOWN_ANI;
	else stateString = HEADUP_ANI;

	return typeString + HYPHEN + stateString;
}

Vector2 CRed_Venus::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = VENUS_RED_BBOX_WIDTH;
	height = VENUS_RED_BBOX_HEIGHT;

	return Vector2(width, height);
}

void CRed_Venus::AutoSwitchState()
{
	//idle down, co tg > going up > idle up, co tg > attack > going down > idle down . het
	if (eState == EnemyState::IDLE_DOWN)
	{
		int a = y;
		GetnxFromMario();
		SwitchState(EnemyState::GOING_UP);
	}
	if (eState == EnemyState::IDLE_UP)
	{
		SwitchState(EnemyState::ATTACK, VENUS_RED_TIME_ATTACK);
		SetBullet();
	}
	if (eState == EnemyState::ATTACK)
	{
		SwitchState(EnemyState::GOING_DOWN);
	}
}

void CRed_Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (eState == EnemyState::GOING_UP)
	{
		
		if (y > yStart - VENUS_RED_BBOX_HEIGHT + 3)
		{
			y -= 3;
		}
		else SetState(EnemyState::IDLE_UP, VENUS_RED_TIME_IDLE_UP);
	}
	
	if (eState == EnemyState::GOING_DOWN)
	{
		if (y < yStart)
		{
			y += 3;
		}
		else SetState(EnemyState::IDLE_DOWN, VENUS_RED_TIME_IDLE_DOWN);
	}

	bullet->Update(dt, &SetObjectCollision());
	CEnemy::Update(dt, coObjects);
	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}

int CRed_Venus::GetnxFromMario()
{
	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
	CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
	LPGAMEOBJECT obj = s->GetPlayer();
	CMario* mario = (CMario*)obj;
	if (mario->GetX() < this->x + VENUS_RED_BBOX_WIDTH)
		return nx = -1;
	return nx = 1;
}

void CRed_Venus::SetBullet()
{
	if (nx > 0)
	{
		bullet->x = this->x + VENUS_RED_BBOX_WIDTH;
	}else bullet->x = this->x - BULLET_VENUS_WIDTH;
	bullet->y = this->y + BULLET_VENUS_WIDTH / 2;
	bullet->vx = 0;
	bullet->vy = 0;
	bullet->nx = this->nx;
	bullet->SetState(EnemyState::ACTION);
}

void CRed_Venus::On_BEING_ATTACKED(int nxCollision)
{
	vx = 0;
	vy = 0;
	this->isHidden = true;
	SetState(EnemyState::BEING_ATTACKED);
}


