#include "MarioSmall.h"

CMarioSmall::CMarioSmall(float x, float y) : CMario(x, y) {

}

void CMarioSmall::Render()
{
	if (vx == 0)
		ani = MARIO_ANI_SMALL_IDLE;
	else if (isRunning)
		ani = MARIO_ANI_SMALL_RUN;
	else ani = MARIO_ANI_SMALL_WALKING;
	if (vy < 0)
	{
		if (isHighJump)
			ani = MARIO_ANI_SMALL_HIGH_JUMP;
		else ani = MARIO_ANI_SMALL_JUMP;
	}
	CMario::Render();
}

void CMarioSmall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_SMALL_BBOX_WIDTH;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT;
}