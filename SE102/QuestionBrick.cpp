#include "QuestionBrick.h"
#include "Mario.h"

CQuestionBrick::CQuestionBrick(float x, float y, float width, float height) : CCollisionBox(x, y, width, height)
{
	yStart = y;
	SetState(QUESTIONBRICK_STATE_NORMAL);
	hasCollided = 0;
}

void CQuestionBrick::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 0)
	{
		if (nyCollision > 0)
			SetState(QUESTIONBRICK_STATE_AFTER_COLLISION);
		
	}
	else return;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		
	if (y + QUESTIONBRICK_GRAVITY * dt < yStart)
	{
		vy += QUESTIONBRICK_GRAVITY * dt;
		hasCollided = 1;
	}
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	if (y > yStart)
	{
		y = yStart;
	}
	/*if(vy!=0)
	DebugOut(ToWSTR("------->" + std::to_string(vy) + "\n").c_str());*/
}

void CQuestionBrick::Render()
{
	string ani;
	if (state == QUESTIONBRICK_STATE_AFTER_COLLISION)
		ani = QUESTIONBRICK_ANI_AFTER_COLLISION;
	else ani = QUESTIONBRICK_ANI_NORMAL;
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	

	RenderBoundingBox();
}

void CQuestionBrick::SetState(int state)
{
	switch (state)
	{
	case QUESTIONBRICK_STATE_AFTER_COLLISION:
		if (hasCollided == 0)
			vy = -QUESTIONBRICK_SPEED_Y * 2;
		this->state = state;
		break;
	case QUESTIONBRICK_STATE_NORMAL:
		this->state = state;
		break;

	default:
		break;
	}
}
