#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include <stdio.h>
#include <math.h>

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
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
	dt = 20;
	// Cap nhat vx, vy dua tren gia toc ax ay
	float vxMax = isRunning ? VELOCITY_X_SPEEDUP_MAX : VELOCITY_X_MAX;
	if (fabs(vx ) < vxMax)
		vx = vx + ax;
	if (vx > 0) f = -0.0045f;
	if (vx < 0) f = 0.0045f;
	if (fabs(vx)>fabs(f))
		vx = vx + f;
	else vx = 0;

	

	/*float vyMax = isHighJump ? VELOCITY_Y_SPEEDUP_MAX : VELOCITY_Y_SPEEDUP;
	if (vy + ay * dt < vxMax)
		vy = vy + ay * dt;*/
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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
		// 0----------------X----------0
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;

		if (ny < 0) {
			vy = 0;
			isStanding = true;
		}


		//
		// Collision logic with other objects
		//
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
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
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
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	ax = 0;
}

void CMario::Render()
{
	
	string ani="ani-small-mario-idle";
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_SMALL_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
				ani = MARIO_ANI_BIG_IDLE;
			else if (isRunning)
				ani = MARIO_ANI_BIG_RUN;
			else ani = MARIO_ANI_BIG_WALK;
			if (vy < 0)
			{
				if(isHighJump)
					ani = MARIO_ANI_BIG_HIGH_JUMP;
				else ani = MARIO_ANI_BIG_JUMP;
			}
				
			//MARIO_ANI_BIG_ROLL ?
			//MARIO_ANI_BIG_SKID ?
			//MARIO_ANI_BIG_ROLL ?
		}
		else if (level == MARIO_LEVEL_SMALL)
			{
			if (vx == 0)
				ani = MARIO_ANI_SMALL_IDLE;
			else if (isRunning)
				ani = MARIO_ANI_SMALL_RUN;
			else ani = MARIO_ANI_SMALL_WALKING;
			if (vy < 0 )
			{
				if (isHighJump)
					ani = MARIO_ANI_SMALL_HIGH_JUMP;
				else ani = MARIO_ANI_SMALL_JUMP;
			}
					
				//MARIO_ANI_SMALL_SKID ?
				//MARIO_ANI_SMALL_RUN ?
			}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			if (vx == 0)
				ani = MARIO_ANI_RACCOON_IDLE;
			else if(isRunning)
				ani = MARIO_ANI_RACCOON_RUN;
			else ani = MARIO_ANI_RACCOON_WALK;
			if (vy < 0)
			{
				ani = MARIO_ANI_RACCOON_JUM;
			}
			if (isAttack)
			{
				ani = MARIO_ANI_RACCOON_ATTACK;
				isAttack = false;
			}
			if (isFly)
			{
				ani = MARIO_ANI_RACCOON_FLY;
				isFly = false;
			}
				//HIGH_JUM?
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (vx == 0)
				ani = MARIO_ANI_FIRE_IDLE;
			else if (isRunning)
				ani = MARIO_ANI_FIRE_RUN; 
			else ani = MARIO_ANI_FIRE_WALK;
			if (vy < 0)
			{
				if (isHighJump)
					ani = MARIO_ANI_FIRE_HIGH_JUMP;
				else ani = MARIO_ANI_FIRE_JUMP;
			}
		}
		else if (level == MARIO_LEVEL_FROG)
		{
			if (vx == 0)
				ani = MARIO_ANI_FROG_IDLE;
			else ani = MARIO_ANI_FROG_WALK;
			if (vy < 0)
			{
				ani = MARIO_ANI_FROG_JUMP;
			}
		}
		else if (level == MARIO_LEVEL_TANOOKI)
		{
			if (vx == 0)
				ani = MARIO_ANI_TANOOKI_IDLE;
			else ani = MARIO_ANI_TANOOKI_WALK;
			if (vy < 0)
			{
				ani = MARIO_ANI_TANOOKI_JUMP;
			}
		}
		else if (level == MARIO_LEVEL_HAMMER)
		{
			if (vx == 0)
				ani = MARIO_ANI_HAMMER_IDLE;
			else ani = MARIO_ANI_HAMMER_WALK;
			if (vy < 0)
			{
				ani = MARIO_ANI_HAMMER_JUMP;
			}
		}
	int alpha = 255;
	if (untouchable) alpha = 128;

	//animation_set->at(ani)->Render(x, y, alpha);
	// DebugOut(CAnimations::GetInstance()->Get(ani))
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
	{
		if(nx<0)
			anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f), alpha);
		else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f), alpha);
	}
	RenderBoundingBox();

}

void CMario::SetLevel(int l)
{
	//previousLevel
	float l1, t1, r1, b1;
	GetBoundingBox(l1, t1, r1, b1);
	level = l; //current
	float l2, t2, r2, b2;
	GetBoundingBox(l2, t2, r2, b2);
	y = y + (b1 - t1) - (b2 - t2)-1;
	
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		//vx = MARIO_WALKING_SPEED;
		ax = 0.010f*3;
		nx = 1;
		isRunning = false;
		break;
	case MARIO_STATE_WALKING_LEFT:
		//vx = -MARIO_WALKING_SPEED;
		ax = -0.010f*3;
		nx = -1;
		isRunning = false;
		break;
	case MARIO_STATE_RUN_RIGHT:
		ax = 0.02f*3;
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUN_LEFT:
		ax = -0.02f*3;
		nx = -1;
		isRunning = true;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (isStanding) {
			isStanding = false;
			vy = -MARIO_JUMP_SPEED_Y*2;
			isHighJump = false;
		}
		break;
	case MARIO_STATE_HIGH_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (isStanding)
		{
			vy = -MARIO_JUMP_SPEED_Y * 1.25*2;
			isHighJump = true;
			isStanding = false;
		}
		break;
	case MARIO_STATE_FLY:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		ax = 0.02f * 4;
		vy = -MARIO_JUMP_SPEED_Y * 1.25;
		isFly = true;
		break;
	case MARIO_STATE_IDLE:
		//vx = 0;
		break;
	case MARIO_STATE_ATTACK:
		//vx = 0;
		break;
	case MARIO_STATE_DIE:
		//vy = -MARIO_DIE_DEFLECT_SPEED;
		ax = 0;
		ay = -0.02f;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_FROG)
	{
		right = x + MARIO_FROG_BBOX_WIDTH;
		if (vx == 0)
			bottom = y + MARIO_FROG_BBOX_HEIGHT;
		else bottom = y + MARIO_FROG_BBOX_HEIGHT_NOT_IDLE;
		
	}
	else if (level == MARIO_LEVEL_TANOOKI)
	{
		if(vx==0)
			right = x + MARIO_TANOOKI_BBOX_WIDTH;
		else right = x + MARIO_TANOOKI_BBOX_WIDTH_NOT_IDLE;
		bottom = y + MARIO_TANOOKI_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		right = x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else {
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


