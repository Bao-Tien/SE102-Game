#include "Koopas.h"
#include "ScenceManager.h"
#include "Game.h"
#include "Mario.h"
#include "MarioConst.h"
#include "PlayScence.h"

CKoopas::CKoopas(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::KOOPAS;
	SetState(EnemyState::LIVE);
	timeWillDie = KOOPAS_TIME_WILL_DIE;
}

string CKoopas::GetAnimationIdFromState()
{
	string typeString, stateString;
	typeString = KOOPAS_ANI;
	if (eState == EnemyState::LIVE) stateString = MOVE_ANI;
	else if (eState == EnemyState::WILL_DIE || eState == EnemyState::DIE || eState == EnemyState::BEING_HELD
		|| eState == EnemyState::BEING_ATTACKED || eState == EnemyState::BEING_KICK)
		stateString = CROUCH_ANI;

	return typeString + HYPHEN + stateString;
}

Vector2 CKoopas::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = KOOPAS_BBOX_WIDTH;
	if (state == EnemyState::WILL_DIE || eState == EnemyState::BEING_HELD || eState == EnemyState::BEING_KICK)
		height = KOOPAS_BBOX_HEIGHT_COUCH;
	else if (state == EnemyState::DIE || state == EnemyState::BEING_ATTACKED)
	{
		height = 0;
		width = 0;
	}
	else height = KOOPAS_BBOX_HEIGHT;
	return Vector2(width, height);
}

void CKoopas::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	CEnemy::CollisionX(coObj, nxCollision, Actively);
	if (Actively == 0)
	{
		if (eState != EnemyState::DIE)
		{
			if (coObj->dt > 1000) return;
			if (dynamic_cast<CMario*>(coObj))
			{
				CMario* mario = (CMario*)coObj;
				if (mario->vxMax == VELOCITY_X_SPEEDUP_MAX) //nhan nut A
				{
					if (eState == EnemyState::WILL_DIE)
					{
						mario->SwitchState(EMarioState::HOLD);
						On_BEING_HELD(); //cam
					}
				}
				else if (mario->mState == EMarioState::WALK)
				{
					if (eState == EnemyState::WILL_DIE)
					{
						On_BEING_KICK(nxCollision);//bi da
					}
					else mario->SwitchType(1);
				}
				else mario->SwitchType(1);
			}
		}
	}

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}

void CKoopas::AutoSwitchState()
{
	if (eState == EnemyState::WILL_DIE)
	{
		SwitchState(EnemyState::LIVE);
	}
	if (eState == EnemyState::BEING_KICK)
	{
		SwitchState(EnemyState::DIE);
	}

	if (eState == EnemyState::BEING_HELD)
	{
		SwitchState(EnemyState::LIVE);
		//mario DIE
		string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
		CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
		LPGAMEOBJECT obj = s->GetPlayer();
		CMario* mario = (CMario*)obj;
		mario->SwitchType(1);
	}
}