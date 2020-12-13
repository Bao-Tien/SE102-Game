#pragma once
#include "CollisionBox.h"

#define TREE_ANI               "ani-tree"
class CTree : public CCollisionBox
{
	virtual void Render();
public:
	CTree(float x, float y, float width, float height);
};

