#pragma once
#include "Square.h"

class CQuestionBrick : public CSquare
{
private:
	float yStart;
	LPGAMEOBJECT magicObj;
public:
	CQuestionBrick(int x, int y, int width, int height);
	string GetAnimationIdFromState();
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void SetMagicObject();
};

