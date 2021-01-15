#include "Green_Venus.h"

CGreen_Venus::CGreen_Venus(float x, float y) : CRed_Venus(x, y)
{
	eGravity = 0;
	eType = EnemyType::GREEN_VENUS;
	yStart = y + 3;
	SetState(EnemyState::IDLE_DOWN, VENUS_RED_TIME_IDLE_DOWN);
	bullet = new CBullet_Venus(x, y);
}

string CGreen_Venus::GetAnimationIdFromState()
{
	string typeString, stateString;

	typeString = VENUS_GREEN_ANI;
	if (eState == EnemyState::GOING_UP || eState == EnemyState::GOING_DOWN) stateString = HEADUP_ANI;
	else if (eState == EnemyState::IDLE_UP || eState == EnemyState::IDLE_DOWN || eState == EnemyState::ATTACK) stateString = HEADDOWN_ANI;
	else stateString = HEADUP_ANI;

	return typeString + HYPHEN + stateString;
}