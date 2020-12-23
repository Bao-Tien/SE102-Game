#include "QuestionBrick.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Game.h"
#include "Scence.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Coin_MagicObj.h"

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
		if (nyCollision > 0) {
			SetState(QUESTIONBRICK_STATE_AFTER_COLLISION);
			if (hasCollided == 0 && y==yStart)
			{
				hasCollided = 1;
				SetMagicObject();
			}
		}
	}
	else return;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (y + QUESTIONBRICK_GRAVITY * dt < yStart)
	{
		vy += QUESTIONBRICK_GRAVITY * dt;
	}
	
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	if (y > yStart)
	{
		y = yStart;
		vy = 0;
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

void CQuestionBrick::SetMagicObject()
{
	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
	CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
	LPGAMEOBJECT obj = s->GetPlayer();
	CMario* mario = (CMario*)obj;
	LPGAMEOBJECT magicObj = new CCoin_MagicObj(x, y);
	if (x == QUESTIONBRICK_X1 || x == QUESTIONBRICK_X2 || x == QUESTIONBRICK_X3 || x == QUESTIONBRICK_X4)
	{
		if (mario->GetType() == EMarioType::SMALL)
			magicObj = new CMushRoom(x, y);
		//else // la
	}
	else
		magicObj = new CCoin_MagicObj(x, y);
	s->AddObjToObjects_Magic(magicObj);
}