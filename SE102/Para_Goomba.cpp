#include "Para_Goomba.h"

CPara_Goomba::CPara_Goomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::PARA_GOOMBA;
}
string CPara_Goomba::GetAnimationIdFromState()
{
	string typeString, stateString;
}