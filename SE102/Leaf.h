#pragma once
#include "GameObject.h"
#include "Magic_Object.h"

class CLeaf : public CMagic_Object
{
public:
	CLeaf(float x, float y);
	Vector2 GetSizeFromType() override;
	string GetAnimationIdFromType() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void AutoSwitchState() override;
};

