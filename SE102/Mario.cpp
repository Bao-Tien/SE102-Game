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
	untouchable = 0;
	mState = EMarioState::IDLE;
	ax = ay = 0;
	f = 0;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	movementRatioX = 1;
	synergies = 0;
	vxMax = VELOCITY_X_MAX;
} 

string CMario::GetAnimationIdFromState()
{
	string typeString, stateString;

	if (mType == EMarioType::SMALL) typeString = "ani-small-mario";
	else if (mType == EMarioType::BIG) typeString = "ani-big-mario";
	else if (mType == EMarioType::RACCOON) typeString = "ani-raccoon-mario";
	else if (mType == EMarioType::FIRE) typeString = "ani-fire-mario";
	else typeString = "ani-small-mario";
	

	if (mState == EMarioState::IDLE) stateString = "idle";
	else if (mState == EMarioState::WALK) stateString = "walk";
	else if (mState == EMarioState::RUN) stateString = "run";
	else if (mState == EMarioState::JUMP) stateString = "jump";
	else if (mState == EMarioState::FLY) stateString = "fly";
	else if (mState == EMarioState::ATTACK) stateString = "attack";
	else if (mState == EMarioState::FALL) stateString = "fall";

	return typeString + "-" + stateString;
}

void CMario::SetState(EMarioState newState, DWORD timeState) {
	this->beginState = GetTickCount();
	this->timeState = timeState;
	mState = newState;
}

bool CMario::SwitchState(EMarioState newState)
{
	if (mState == EMarioState::DIE) return false;
	if (GetTickCount() < beginState + timeState) return false;
	else if (newState == EMarioState::DIE) {
		SetState(newState);
		return true;
	}
	else if (newState == EMarioState::ATTACK)
	{
		SetState(newState, 500);
		return true;
	}
	else if (newState == EMarioState::JUMP) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::RUN)
		{
			SetState(newState);
			return true;
		}
	}
	else if (newState == EMarioState::FLY) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::RUN)
		{
			SetState(newState);
			return true;
		}
	}
	else if (newState == EMarioState::FALL) {
		if (mState == EMarioState::JUMP || mState == EMarioState::FLY)
		{
			SetState(newState);
			return true;
		}
	}
	else if (newState == EMarioState::WALK) {
		if (mState == EMarioState::IDLE || mState == EMarioState::RUN || mState == EMarioState::JUMP || mState == EMarioState::FLY || mState == EMarioState::ATTACK)
		{
			SetState(newState);
			return true;
		}
	}
	else if (newState == EMarioState::RUN) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::JUMP || mState == EMarioState::FLY || mState == EMarioState::ATTACK)
		{
			SetState(newState);
			return true;
		}
	}
	else if (newState == EMarioState::IDLE) {
		if (mState == EMarioState::WALK || mState == EMarioState::RUN || mState == EMarioState::JUMP || mState == EMarioState::FLY || mState == EMarioState::ATTACK)
		{
			SetState(newState);
			return true;
		}
	}
	
	return false;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isHidden) return;
	/*if (ax > MARIO_ACCELERATION_WALK && synergies < 6) synergies++;
	else if (synergies > 0) synergies--;*/
	synergies = 0;

	DebugOut(ToWSTR(std::to_string(synergies) + "\n").c_str());
	//float vxMax = mState == EMarioState::RUN ? VELOCITY_X_SPEEDUP_MAX : VELOCITY_X_MAX;
	
	if (fabs(vx + ax*dt) < vxMax) {
		vx = vx + ax * dt;
	}
		
	if (vx > 0) f = -MARIO_FRICTION;
	if (vx < 0) f = MARIO_FRICTION;
	if (fabs(vx) > fabs(f))
		vx = vx + f;
	else vx = 0;

	//float vyMax = mState==EMarioState::JUMP ? 

	vy += MARIO_GRAVITY * dt;
	
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (mState != EMarioState::DIE)
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

		if (nx != 0)
		{
			vx = 0;
		}

		if (ny < 0 && vx==0) {
			vy = 0;
			SwitchState(EMarioState::IDLE);
		}
		if (ny < 0 && vx != 0 && fabs(vx) < VELOCITY_X_MAX) {
			vy = 0;
			SwitchState(EMarioState::WALK);
		}
		if (ny < 0 && fabs(vx) > VELOCITY_X_MAX)
		{
			vy = 0;
			SwitchState(EMarioState::RUN);
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
						goomba->SetState(GOOMBA_STATE_WILL_DIE);  
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (mState == EMarioState::ATTACK)
							{
								if (dynamic_cast<CGoomba*>(e->obj))
								{
									((CGoomba*)(e->obj))->SetState(GOOMBA_STATE_BEING_SHOOTED, nx);
								}
							}
							/*else if (this != dynamic_cast<CMarioSmall*>(this))
							{
								LPSCENE scence = CScences::GetInstance()->Get(CGame::GetInstance()->GetCurrentSceneId());
								scence->SwitchPlayer(new CMarioSmall(this->x, this->y));
								StartUntouchable();
							}*/
							//else mState = EMarioState::DIE;
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
	movementRatioX = 1;
	vxMax = VELOCITY_X_MAX;
}

void CMario::Render()
{
	int alpha = 255;
	if (untouchable) alpha = 128;

	LPANIMATION anim = CAnimations::GetInstance()->Get(GetAnimationIdFromState());
	
	if (anim != NULL)
	{
		if(nx==-1)
			anim->Render(x , y , D3DXVECTOR2(-1.0f, 1.0f), alpha);
		else 
			anim->Render(x , y , D3DXVECTOR2(1.0f, 1.0f), alpha);
			
	}
	//CSprites::GetInstance()->Get("spr-raccoon-mario-spin-5")->Draw(x, y, Vector2(1.0f,1.0f));
	
	//RenderBoundingBox();
}

void CMario::KeyboardHandle(int key, bool type)
{
	switch (key)
	{
	case KEYBOARD_PRESS_A:
		if (type)
		{
			vxMax = VELOCITY_X_SPEEDUP_MAX;
			movementRatioX = 1.5f;
		}
		break;
	case KEYBOARD_PRESS_RIGHT:
		ax = MARIO_ACCELERATION_WALK * movementRatioX;
		nx = 1;
		break;
	case KEYBOARD_PRESS_LEFT:
		ax = -MARIO_ACCELERATION_WALK * movementRatioX;
		nx = -1;
		break;
	case KEYBOARD_PRESS_X:
		if (SwitchState(EMarioState::JUMP)) {
			vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case KEYBOARD_PRESS_S:
		if (!type) // nhay cao
		{
			if (synergies == 6)
				SwitchState(EMarioState::FLY);
			else
				if (SwitchState(EMarioState::JUMP)) 
				{
					vy = -MARIO_HIGH_JUMP_SPEED_Y;
				}
		}
		//else //nhay cao hon
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
	mType = EMarioType::SMALL;
	mState = EMarioState::IDLE;
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


