#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CMagic_Object(x, y)
{
	On_ACTIVE_OF_LEAF();
}

string CLeaf::GetAnimationIdFromType()
{
	return LEAF_ANI;
}

Vector2 CLeaf::GetSizeFromType()
{
	return Vector2(LEAF_BBOX_WIDTH, LEAF_BBOX_HEIGHT);
}

void CLeaf::AutoSwitchState()
{
	if (mgState == MagicState::ACTIVE)
	{
		SwitchState(MagicState::LEFT, LEAF_TIME_LEFT);
		On_LEFT();
	}
		
	if (mgState == MagicState::LEFT)
	{
		SwitchState(MagicState::RIGHT, LEAF_TIME_RIGHT);
		On_RIGHT();
	}
	if (mgState == MagicState::RIGHT)
	{
		SwitchState(MagicState::LEFT, LEAF_TIME_LEFT);
		On_LEFT();
	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float vyMax = 0.10f;
	vy += GetGravity() * dt;
	if (vy > vyMax) vy = vyMax;
	CGameObject::Update(dt);
	CollisionWithObj(&SetObjectCollision());
	AutoSwitchState();


	/*DebugOut(ToWSTR(std::to_string((int)mgState) + "\n").c_str());*/
	DebugOut(ToWSTR(std::to_string(dx) + "\n").c_str());
}

