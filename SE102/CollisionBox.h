#pragma once
#include "GameObject.h"

class CCollisionBox : public CGameObject
{
protected:
	int width, height;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

public:
	CCollisionBox(int x, int y, int width, int height);
	virtual void Render();
};

