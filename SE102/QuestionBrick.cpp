#include "QuestionBrick.h"
#include "Mario.h"

CQuestionBrick::CQuestionBrick(float x, float y, float width, float height) : CCollisionBox(x, y, width, height)
{
	yStart = y;
	yEnd = y + height * 2 / 3;
}

void CQuestionBrick::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 0)
	{
		if (nyCollision > 0)
			SetState(QUESTIONBRICK_STATE_AFTER_COLLISION);
		/*if (dynamic_cast<CMario*>(coObj))
		{*/
		//
		//}
	}
	else return;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y < yStart)
		vy += QUESTIONBRICK_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

void CQuestionBrick::Render()
{
	string ani = QUESTIONBRICK_ANI_NORMAL;
	if (state == QUESTIONBRICK_STATE_AFTER_COLLISION)
		ani = QUESTIONBRICK_ANI_AFTER_COLLISION;
	LPANIMATION anim = CAnimations::GetInstance()->Get("ani-question-block");
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	

	RenderBoundingBox();
}

void CQuestionBrick::SetState(int state)
{
	switch (state)
	{
	case QUESTIONBRICK_STATE_AFTER_COLLISION:
		vy = -QUESTIONBRICK_SPEED_Y;
		this->state = state;
		break;

	default:
		break;
	}
}
