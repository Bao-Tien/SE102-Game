#include "MarioBig.h"

CMarioBig::CMarioBig(float x, float y) : CMario(x, y) {
	mType = EMarioType::BIG;
}

void CMarioBig::Render()
{
	CMario::Render();
}

void CMarioBig::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;
}