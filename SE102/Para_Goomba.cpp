#include "Para_Goomba.h"
#include "Mario.h"

CPara_Goomba::CPara_Goomba(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::PARA_GOOMBA;
	SetState(EnemyState::LIVE, PARA_GOOMBA_TIME_LIVE);
}

string CPara_Goomba::GetAnimationIdFromState()
{//di 3 buoc(live), nhay 3 buoc nho(jump), nhay 1 buoc lon (hight_jump)
	string typeString, stateString;
	if (level == 2) {
		if (eState == EnemyState::LIVE || eState == EnemyState::BEING_ATTACKED)
		{
			typeString = PARA_GOOMBA_ANI;
			stateString = IDLE_ANI;
		}
		else if (eState == EnemyState::JUMP)
		{
			typeString = PARA_GOOMBA_ANI;
			stateString = IDLE_ANI;
		}
		else if (eState == EnemyState::FLY)
		{
			typeString = PARA_GOOMBA_ANI;
			stateString = FLY_ANI;
		}
	}
	else if (level == 1) {
		if (eState == EnemyState::LIVE || eState == EnemyState::BEING_ATTACKED)
		{
			typeString = RED_GOOMBA_ANI;
			stateString = IDLE_ANI;
		}
	}
	else if (level == 0) {

	}
	
	return typeString + HYPHEN + stateString;
}

Vector2 CPara_Goomba::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = KOOPAS_BBOX_WIDTH;
	if (state == EnemyState::LIVE)
		height = RED_GOOMBA_BBOX_HEIGHT;
	else if (state == EnemyState::WILL_DIE)
		height = RED_GOOMBA_BBOX_HEIGHT_DIE;
	else if (state == EnemyState::JUMP)
		height = PARA_BBOX_HEIGHT;
	else if (state == EnemyState::FLY)
		height = PARA_BBOX_FLY_HEIGHT;
	else if (state == EnemyState::DIE || state == EnemyState::BEING_ATTACKED)
	{
		height = 0;
		width = 0;
	}
	else height = RED_GOOMBA_BBOX_HEIGHT;
	return Vector2(width, height);
}

void CPara_Goomba::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	CEnemy::CollisionY(coObj, nyCollision, Actively);
	if (Actively == 0)
	{
		if (eState != EnemyState::DIE)
		{
			if (dynamic_cast<CMario*>(coObj))
			{
				if (nyCollision < 0) {
					if (level > 0) level--;
					if (level == 1) SetState(EnemyState::LIVE);
				}
				else {
					CMario* mario = (CMario*)coObj;
					mario->SwitchType(1);
				}
				
				
			}
		}
	}
	else
	{
		if (eState == EnemyState::FLY)
			On_FLY();
		else if (eState == EnemyState::JUMP)
			On_JUMP();
	}
}

void CPara_Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}

void CPara_Goomba::AutoSwitchState()
{
	if (level == 2) {
		if (eState == EnemyState::LIVE)
		{
			SwitchState(EnemyState::JUMP, PARA_GOOMBA_TIME_JUMP);
		}
		if (eState == EnemyState::JUMP)
		{
			SwitchState(EnemyState::FLY, PARA_GOOMBA_TIME_FLY);
		}
		if (eState == EnemyState::FLY)
		{
			SwitchState(EnemyState::LIVE, PARA_GOOMBA_TIME_LIVE);
		}
	}
	
}