#include "QuestionBrick.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Game.h"
#include "Scence.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Coin_MagicObj.h"
#include "Leaf.h"

CQuestionBrick::CQuestionBrick(int x, int y, int width, int height) : CSquare(x, y, width, height)
{
	yStart = y;
	SetState(SquareState::NORMAL);
	bGravity = BRICK_GRAVITY;
}

string CQuestionBrick::GetAnimationIdFromState()
{
	if (bState == SquareState::NORMAL) return QUESTIONBRICK_ANI_NORMAL;
	else return QUESTIONBRICK_ANI_AFTER_COLLISION;
}

void CQuestionBrick::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	
}

void CQuestionBrick::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 0)
	{
		if (dynamic_cast<CMario*>(coObj))
		{
			if (nyCollision > 0) {
				if (bState == SquareState::NORMAL)
				{
					On_AFTER_COLLISION();
					SetMagicObject();

				}
			}
		}
	}
	else return;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y + BRICK_GRAVITY * dt < yStart)
	{
		vy += BRICK_GRAVITY * dt;
	}
	CSquare::Update(dt, coObjects);
	if (y > yStart)
	{
		y = yStart;
		vy = 0;
	}
}

void CQuestionBrick::SetMagicObject()
{
	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
	CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
	LPGAMEOBJECT obj = s->GetPlayer();
	CMario* mario = (CMario*)obj;
	magicObj;
	if (mario->GetType() == EMarioType::SMALL)
	{
		if (x == QUESTIONBRICK_X2 || x == QUESTIONBRICK_X3 || x == QUESTIONBRICK_X4)
		{

			magicObj = new CMushRoom(x, y);
		}
		else if (x == QUESTIONBRICK_X1)
		{
			magicObj = new CLeaf(x, y);
		}
		else magicObj = new CLeaf(x, y);
	}
	else {
		magicObj = new CCoin_MagicObj(x, y);
		s->AddPoint(100);
	}
		
	s->AddObjToObjects_Magic(magicObj);
}