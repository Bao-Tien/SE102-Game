#include "MarioBig.h"

CMarioBig::CMarioBig(float x, float y) : CMario(x, y) {

}

void CMarioBig::Render()
{
	if (vx == 0)
		ani = MARIO_ANI_BIG_IDLE;
	else if (isRunning)
		ani = MARIO_ANI_BIG_RUN;
	else ani = MARIO_ANI_BIG_WALK;
	if (vy < 0)
	{
		if (isHighJump)
			ani = MARIO_ANI_BIG_JUMP;
		else ani = MARIO_ANI_BIG_JUMP;
	}
	CMario::Render();
}

void CMarioBig::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;
}