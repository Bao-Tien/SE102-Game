#pragma once
#include "Mario.h"

class CMarioSmall : public CMario
{

public:
	CMarioSmall(float x = 0.0f, float y = 0.0f);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

