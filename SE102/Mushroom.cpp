#include "MushRoom.h"
#include "Mario.h"
#include "QuestionBrick.h"

CMushRoom::CMushRoom(float x, float y) : CMagic_Object(x,y)
{
	yStart = y;
	SetState(MagicState::ACTIVE);
}

string CMushRoom::GetAnimationIdFromType()
{
	return MUSHROOM_ANI;
}

Vector2 CMushRoom::GetSizeFromType()
{
	return Vector2(MUSHROOM_BBOX_WIDTH, MUSHROOM_BBOX_HEIGHT);
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (mgState == MagicState::ACTIVE)
	{
		if (y > yStart - MUSHROOM_BBOX_HEIGHT)
		{
			y -= 2;
			return;
		}
		else On_MOVE();
	}
	CMagic_Object::Update(dt, coObjects);

	//DebugOut(ToWSTR(std::to_string((int)mgState) + "\n").c_str());
}
