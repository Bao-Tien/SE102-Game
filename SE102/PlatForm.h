#pragma once
#include "GameObject.h"

class CPlatForm : public CGameObject
{
protected:
	int width, height;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	CPlatForm(int x, int y, int width, int height);
	virtual void Render();
};

