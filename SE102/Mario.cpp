#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include <stdio.h>
#include <math.h>

#include "MarioSmall.h"
#include "MarioBig.h"
#include "MarioRaccoon.h"
#include "PlayScence.h"
#include "Scence.h"
#include "ScenceManager.h"

CMario::CMario(float x, float y) : CGameObject()
{
	isStanding = false;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	isHighJump = false;
	isRunning = false;
	isAttack = false;
	isFly = false;
	ax = ay = 0;
	f = 0;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
} 

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float vxMax = isRunning ? VELOCITY_X_SPEEDUP_MAX : VELOCITY_X_MAX;
	
	if (fabs(vx + ax) < vxMax)
		vx = vx + ax * dt;
	if (vx > 0) f = -0.0045f;
	if (vx < 0) f = 0.0045f;
	if (isStanding)
	{
		if (fabs(vx) > fabs(f))
			vx = vx + f;
		else vx = 0;
	}

	vy += MARIO_GRAVITY * dt;
	
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;

		if (ny < 0) {
			vy = 0;
			isStanding = true;
			isFly = false;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);  
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (this != dynamic_cast<CMarioSmall*>(this))
							{
								LPSCENE scence = CScences::GetInstance()->Get(CGame::GetInstance()->GetCurrentSceneId());
								scence->SwitchPlayer(new CMarioSmall(this->x, this->y));
								StartUntouchable();
							}
							else SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(std::to_string(p->GetSceneId()));
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	ax = 0;
}

void CMario::Render()
{
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_SMALL_DIE;

	int alpha = 255;
	if (untouchable) alpha = 128;

	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
	{
		if(nx<0)
			anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f), alpha);
		else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f), alpha);
	}
	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		ax = MARIO_ACCELERATION_WALK;
		nx = 1;
		isRunning = false;
		break;
	case MARIO_STATE_WALKING_LEFT:
		ax = -MARIO_ACCELERATION_WALK;
		nx = -1;
		isRunning = false;
		break;
	case MARIO_STATE_RUN_RIGHT:
		ax = MARIO_ACCELERATION_RUN;
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUN_LEFT:
		ax = -MARIO_ACCELERATION_RUN;
		nx = -1;
		isRunning = true;
		break;
	case MARIO_STATE_JUMP:
		if (isStanding) {
			isStanding = false;
			vy = -MARIO_JUMP_SPEED_Y;
			isHighJump = false;
		}
		break;
	case MARIO_STATE_HIGH_JUMP:
		if (isStanding)
		{
			vy = -MARIO_HIGH_JUMP_SPEED_Y;
			isHighJump = true;
			isStanding = false;
		}
		break;
	case MARIO_STATE_IDLE:
		break;
	case MARIO_STATE_ATTACK:
		break;
	case MARIO_STATE_DIE:
		ax = 0;
		ay = -MARIO_ACCELERATION_DIE;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


