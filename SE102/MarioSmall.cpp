#include "MarioSmall.h"

CMarioSmall::CMarioSmall(float x, float y) : CMario(x, y) {
	mType = EMarioType::SMALL;
}

void CMarioSmall::Render()
{
	CMario::Render();
}

void CMarioSmall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_SMALL_BBOX_WIDTH;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT;
}