#pragma once
#include "Magic_Object.h"
#include "MagicConst.h"


class CCoin_MagicObj : public CMagic_Object
{
public:
	CCoin_MagicObj(float x, float y);
	Vector2 GetSizeFromType() override;
	string GetAnimationIdFromType() override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
};

