#include "MarioSelectScence.h"
#include "Game.h"

CMarioSelectScence::CMarioSelectScence(float x, float y) :CGameObject()
{
	this->x = x;
	this->y = y;
}

void CMarioSelectScence::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_SELECTION_BBOX_WIDTH;
	bottom = y + MARIO_SELECTION_BBOX_HEIGHT;
}
void CMarioSelectScence::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	vx = 0;
}
void CMarioSelectScence::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}
void CMarioSelectScence::Render()
{
	int alpha = 255;

	LPANIMATION anim = CAnimations::GetInstance()->Get("ani-small-mario-idle-front");

	if (anim != NULL)
	{
		anim->Render(x-10, y-20, D3DXVECTOR2(1.0f, 1.0f), alpha);
		//anim->Render(80, 140, D3DXVECTOR2(1.0f, 1.0f), alpha);
	}
	RenderBoundingBox();
}
void CMarioSelectScence::KeyboardHandle(int key)
{
	switch (key)
	{
	case KEYBOARD_PRESS_RIGHT:
		vx = MARIO_SELECTION_VELOCITY;
		vy = 0;
		break;
	case KEYBOARD_PRESS_LEFT:
		vx = -MARIO_SELECTION_VELOCITY;
		vy = 0;
		break;
	case KEYBOARD_PRESS_DOWN:
		vy = MARIO_SELECTION_VELOCITY;
		vx = 0;
		break;
	case KEYBOARD_PRESS_UP:
		vy = -MARIO_SELECTION_VELOCITY;
		vx = 0;
		break;
	default:
		vy=vx=0;
		break;
	}

}