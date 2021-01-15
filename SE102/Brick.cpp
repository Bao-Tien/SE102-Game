#include "Brick.h"
#include "Mario.h"
#include "AnimationManager.h"

CBrick::CBrick(int x, int y, int width, int height) : CSquare(x, y, width, height)
{
	SetState(SquareState::NORMAL);
	r = 0;
}

string CBrick::GetAnimationIdFromState()
{
	if (bState == SquareState::NORMAL) return BRICK_ANI_NORMAL;
	else if (bState == SquareState::BROKEN) return BRICK_ANI_BROKEN;
}

void CBrick::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (Actively == 0)
	{
		if (dynamic_cast<CMario*>(coObj))
		{
			CMario* mario = (CMario*)coObj;
			if (mario->mState == EMarioState::ATTACK)
			{
				On_BROKEN();
				SetPoinCenter();
			}
		}
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (bState == SquareState::BROKEN) {
		r += 0.16 * dt;
		CSquare::Update(dt, coObjects);
	}
		
}

void CBrick::Render()
{
	if (bState == SquareState::NORMAL)
		CSquare::Render();
	else if (bState == SquareState::BROKEN)
	{
		Vector2 tScale = Vector2(0.7f, 0.7f);
		CAnimations::GetInstance()->Get(GetAnimationIdFromState())->Render(x + r * 1, y + r * 1, tScale);
		CAnimations::GetInstance()->Get(GetAnimationIdFromState())->Render(x + r * 1, y + r * -1, tScale);
		CAnimations::GetInstance()->Get(GetAnimationIdFromState())->Render(x + r * -1, y + r * 1, tScale);
		CAnimations::GetInstance()->Get(GetAnimationIdFromState())->Render(x + r * -1, y + r * -1, tScale);
	}
}

void CBrick::SetPoinCenter()
{
	x = x + width / 2;
	y = y + height / 2;
}