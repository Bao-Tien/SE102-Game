#pragma once
#include "Transform.h"
#include "GameObject.h"


class CCanGo : public CGameObject
{
protected:
	Vector2 beginPosition;
	Vector2 size;


public:
	CCanGo(Vector2,Vector2);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	void Render() {};
};

