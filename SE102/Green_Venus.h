#pragma once
#include "Red_Venus.h"

class CGreen_Venus : public CRed_Venus
{
public:
	CGreen_Venus(float x, float y);
	virtual string GetAnimationIdFromState();
};

