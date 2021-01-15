#pragma once
#include "MagicConst.h"
#include "Magic_Object.h"


class CMushRoom : public CMagic_Object
{
private:
	float yStart;
public:
	CMushRoom(float x, float y);
	Vector2 GetSizeFromType() override;
	string GetAnimationIdFromType() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
};

