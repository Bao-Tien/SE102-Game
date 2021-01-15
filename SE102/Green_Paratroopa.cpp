#include "Green_Paratroopa.h"
#include "Mario.h"

CGreen_Paratroopa::CGreen_Paratroopa(float x, float y) : CGreen_Koopas(x, y)
{
	eType = EnemyType::GREEN_PARATROOPA;
	SetState(EnemyState::VIP);
}

string CGreen_Paratroopa::GetAnimationIdFromState()
{
	return PARATROPA_ANI;
}

Vector2 CGreen_Paratroopa::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = PARATROPA_WIDTH;
	height = PARATROPA_HEIGHT;
	if (state == EnemyState::DIE || state == EnemyState::BEING_ATTACKED)
	{
		height = 0;
		width = 0;
	}
	return Vector2(width, height);
}

void CGreen_Paratroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	//DebugOut(ToWSTR(std::to_string((int)eState) + "\n").c_str());
}

void CGreen_Paratroopa::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	
	if (eState == EnemyState::VIP)
	{
		if (eState != EnemyState::DIE)
		{
			if (Actively == 1)
			{
				if (nyCollision < 0)
				{
					vy = -PARATROPA_SPEED_Y;
					vx = -PARATROPA_SPEED_X;
				}
				else vy = 0;
			}
		}
	}
	else CKoopas::CollisionY(coObj, nyCollision, Actively);
}
