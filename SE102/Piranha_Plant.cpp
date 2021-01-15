#include "Piranha_Plant.h"
#include "Mario.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Game.h"
#include "GameObject.h"

CPiranha_Plant::CPiranha_Plant(float x, float y) : CEnemy(x, y)
{
	eGravity = 0;
	eType = EnemyType::PIRANHA_PLANT;
	yStart = y + 3;
	SetState(EnemyState::IDLE_DOWN, VENUS_RED_TIME_IDLE_DOWN);
}

string CPiranha_Plant::GetAnimationIdFromState()
{
	return PIRANHA_PLANT_VENUS_ANI;
}

Vector2 CPiranha_Plant::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = PIRANHA_PLANT_BBOX_WIDTH;
	height = PIRANHA_PLANT_BBOX_HEIGHT;

	return Vector2(width, height);
}

void CPiranha_Plant::AutoSwitchState()
{
	if (eState == EnemyState::IDLE_DOWN)
	{
		SwitchState(EnemyState::GOING_UP);
	}
	if (eState == EnemyState::IDLE_UP)
	{
		SwitchState(EnemyState::GOING_DOWN);
	}
}

void CPiranha_Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (eState == EnemyState::GOING_UP)
	{

		if (y > yStart - PIRANHA_PLANT_BBOX_HEIGHT + 3)
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

	CEnemy::Update(dt, coObjects);
	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}

void CPiranha_Plant::On_BEING_ATTACKED(int nxCollision)
{
	vx = 0;
	vy = 0;
	this->isHidden = true;
	SetState(EnemyState::BEING_ATTACKED);
}
