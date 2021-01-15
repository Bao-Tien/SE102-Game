#include "Square.h"
#include "Mario.h"

CSquare::CSquare(int x, int y, int width, int height) : CCollisionBox(x, y, width, height)
{
	this->isHidden = false;
}

void CSquare::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	CCollisionBox::GetBoundingBox(left, top, right, bottom);
	if (bState == SquareState::BROKEN)
	{
		left = top = right = bottom = 0;
		return;
	}
}

void CSquare::SwitchState(SquareState newState, DWORD timeNewState)
{
	if (GetTickCount() - beginState >= timeState)
		SetState(newState, timeNewState);
}

void CSquare::On_AFTER_COLLISION()
{
	vy = -QUESTIONBRICK_SPEED_Y;
	SetState(SquareState::AFTER_COLLISION);
}

void CSquare::On_BROKEN()
{
	vy = -BRICK_SPEED_Y;
	vx = 0;
	bGravity = BRICK_GRAVITY;
	SetState(SquareState::BROKEN);
}

void CSquare::NoCollision()
{
	CGameObject::NoCollision();
}

void CSquare::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += GetGravity() * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	AutoSwitchState();
}

string CSquare::GetAnimationIdFromState()
{
	return DEFINE_ANI;
}

void CSquare::Render()
{
	string ani = GetAnimationIdFromState();
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
	{
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	}
	RenderBoundingBox();
}

void CSquare::SetState(SquareState newState, DWORD timeNewState)
{
	beginState = GetTickCount();
	timeState = timeNewState;
	bState = newState;
}