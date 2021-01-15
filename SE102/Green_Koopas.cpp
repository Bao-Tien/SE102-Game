#include "Green_Koopas.h"

CGreen_Koopas::CGreen_Koopas(float x, float y) : CKoopas(x, y)
{
	eType = EnemyType::GREEN_KOOPAS;
	SetState(EnemyState::LIVE);
	timeWillDie = KOOPAS_TIME_WILL_DIE;
}

string CGreen_Koopas::GetAnimationIdFromState()
{
	string typeString, stateString;
	typeString = GREEN_KOOPAS_ANI;
	if (eState == EnemyState::LIVE) stateString = MOVE_ANI;
	else if (eState == EnemyState::WILL_DIE || eState == EnemyState::DIE || eState == EnemyState::BEING_HELD
		|| eState == EnemyState::BEING_ATTACKED || eState == EnemyState::BEING_KICK)
		stateString = CROUCH_ANI;

	return typeString + HYPHEN + stateString;
}