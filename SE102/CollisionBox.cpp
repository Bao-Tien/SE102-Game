#include "CollisionBox.h"


CCollisionBox::CCollisionBox(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CCollisionBox::Render()
{
	RenderBoundingBox();
}

void CCollisionBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}