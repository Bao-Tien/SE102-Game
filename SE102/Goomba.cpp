#include "Goomba.h"
#include "Mario.h"

CGoomba::CGoomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::GOOMBA;
	SetState(EnemyState::LIVE);
	timeWillDie = GOOMBA_TIME_WILL_DIE;
}

string CGoomba::GetAnimationIdFromState()
{
	string typeString, stateString;
	 
	typeString = GOOMBA_ANI;
	if (eState == EnemyState::DIE) stateString = DIE_ANI;
	else if (eState == EnemyState::WILL_DIE) stateString = DIE_ANI;
	else if (eState == EnemyState::BEING_ATTACKED) stateString = IDLE_ANI;
	else stateString = WALK_ANI;

	return typeString + HYPHEN + stateString;
}

Vector2 CGoomba::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = GOOMBA_BBOX_WIDTH;
	if (state == EnemyState::WILL_DIE)
		height = GOOMBA_BBOX_HEIGHT_DIE;
	else if (state == EnemyState::DIE || state == EnemyState::BEING_ATTACKED)
	{
		height = 0;
		width = 0;
	}
	else height = GOOMBA_BBOX_HEIGHT;
	return Vector2(width, height);
}

void CGoomba::AutoSwitchState()
{
	if (eState == EnemyState::WILL_DIE)
	{
		SwitchState(EnemyState::DIE);
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}
