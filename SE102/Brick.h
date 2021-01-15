#pragma once
#include "Square.h"

class CBrick : public CSquare
{
	float r;
public:
	CBrick(int x, int y, int width, int height);
	string GetAnimationIdFromState();
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;
	void SetMagicObject();
	void SetPoinCenter();
};

