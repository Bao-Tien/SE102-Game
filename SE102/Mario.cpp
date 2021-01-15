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
#include "MarioFire.h"
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
	else if (mState == EMarioState::FALL_SLIGHTLY) stateString = "fall-slightly";
	else if (mState == EMarioState::DIE) stateString = "die";
	else if (mState == EMarioState::HOLD) stateString = "hold";
	else stateString = "idle";

	return typeString + "-" + stateString;
}

void CMario::SetState(EMarioState newState, DWORD timeState) {
	this->beginState = GetTickCount();
	this->timeState = timeState;
	mState = newState;
}

bool CMario::SwitchState(EMarioState newState, DWORD newTimeState)
{
	if (mState == EMarioState::DIE || mState == EMarioState::REMEMBER) return false;
	if (GetTickCount() < this->beginState + this->timeState) return false;

	else if (newState == EMarioState::DIE) {
		vy = -MARIO_HIGH_JUMP_SPEED_Y;
		vx = 0;
		SetState(newState, newTimeState);
		return true;
	}
	else if (newState == EMarioState::ATTACK)
	{
		SetState(newState, newTimeState);
		return true;
	}
	else if (newState == EMarioState::JUMP) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::RUN || mState == EMarioState::ATTACK)
		{
			SetState(newState, newTimeState);
			vy = -MARIO_HIGH_JUMP_SPEED_Y;
			return true;
		}
	}
	else if (newState == EMarioState::FLY) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::RUN
			|| mState == EMarioState::FALL || mState == EMarioState::JUMP)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::FALL) {
		if (mState == EMarioState::JUMP || mState == EMarioState::FLY || mState == EMarioState::FALL_SLIGHTLY)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::FALL_SLIGHTLY) {

		if (mState == EMarioState::FALL)
		{
			SetState(newState, newTimeState);
			vy = 0;
			return true;
		}
	}
	else if (newState == EMarioState::WALK) {
		if (mState == EMarioState::IDLE || mState == EMarioState::RUN || mState == EMarioState::JUMP
			|| mState == EMarioState::FLY || mState == EMarioState::ATTACK || mState == EMarioState::FALL)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::RUN) {
		if (mState == EMarioState::IDLE || mState == EMarioState::WALK || mState == EMarioState::JUMP
			|| mState == EMarioState::FLY || mState == EMarioState::ATTACK || mState == EMarioState::FALL)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::IDLE) {
		if (mState == EMarioState::WALK || mState == EMarioState::RUN || mState == EMarioState::JUMP
			|| mState == EMarioState::FALL || mState == EMarioState::ATTACK || vxMax != VELOCITY_X_SPEEDUP_MAX)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::HOLD) {
		if (vxMax == VELOCITY_X_SPEEDUP_MAX)
		{
			SetState(newState, newTimeState);
			return true;
		}
	}
	else if (newState == EMarioState::REMEMBER) {
		SetState(newState, newTimeState);
		return true;
	}

	return false;
}

void CMario::MarioAfterCollisionYWithEnemy() //nay len
{
	vy = -MARIO_JUMP_SPEED_Y;
}

void CMario::NoCollision()
{
	CGameObject::NoCollision();
	if (synergies > 0) synergies -= 2;
	if (dy > 0) {
		SwitchState(EMarioState::FALL);
	}
}
void CMario::SwitchType(int typeObj)
{
	
	if (typeObj == 1) //nen lam giong magic
	{
		if (mState != EMarioState::ATTACK)
		{
			vx = 0;
			/*if (mType != EMarioType::SMALL) {
				SwitchState(EMarioState::REMEMBER);
			}*/
			//else SwitchState(EMarioState::DIE);

			//if (mType != EMarioType::SMALL) {
			//	SwitchState(EMarioState::DIE);
			//}
			////else SwitchState(EMarioState::DIE);
			//else {
			//	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
			//	LPSCENE s = CScences::GetInstance()->Get(currentScenceId);
			//	if (mType == EMarno cioType::FIRE)
			//		s->SwitchPlayer(new CMarioRaccoon(x, y));
			//	else if (mType == EMarioType::RACCOON)
			//		s->SwitchPlayer(new CMarioBig(x, y));
			//	else if (mType == EMarioType::BIG)
			//		s->SwitchPlayer(new CMarioSmall(x, y));
			//}
					string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
					LPSCENE s = CScences::GetInstance()->Get(currentScenceId);
					if (mType == EMarioType::SMALL)
						SwitchState(EMarioState::DIE);
					else if (mType == EMarioType::BIG)
						s->SwitchPlayer(new CMarioSmall(x, y));
					/*else if (mType == EMarioType::RACCOON)
						s->SwitchPlayer(new CMarioBig(x, y));*/
					else if (mType == EMarioType::FIRE)
						s->SwitchPlayer(new CMarioRaccoon(x, y));
						//}
		}
	}
	else //magic
	{
		string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
		LPSCENE s = CScences::GetInstance()->Get(currentScenceId);
		//LPGAMEOBJECT player = s->GetPlayer();
		if (mType == EMarioType::SMALL)
			s->SwitchPlayer(new CMarioBig(x, y));
		else if (mType == EMarioType::BIG)
			s->SwitchPlayer(new CMarioRaccoon(x, y));
		else if (mType == EMarioType::RACCOON)
			s->SwitchPlayer(new CMarioFire(x, y));
	}

}
void CMario::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (mState == EMarioState::ATTACK) {
		if (hasAttack == false) hasAttack = true;
		else return;
	}
	coObj->CollisionX(this, nxCollision, 0);
}

void CMario::OnHadCollided(LPGAMEOBJECT coObj) {
	if (mState == EMarioState::ATTACK) {
		if (dx > 0) {
			CollisionX(coObj, -1, 1);
		}
		else {
			CollisionX(coObj, 1, 1);
		}
	}
}

void CMario::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{

	if (nyCollision < 0)
	{
		if (vx != 0 && fabs(vx) < VELOCITY_X_MAX)
		{
			vy = 0;
			SwitchState(EMarioState::WALK);
		}
		if (fabs(vx) > VELOCITY_X_MAX)
		{
			vy = 0;
			SwitchState(EMarioState::RUN);
			if (synergies < 1000) synergies += 25;
		}
		if (vx == 0)
		{
			if (synergies > 0) synergies -= 10;
			SwitchState(EMarioState::IDLE);
		}
	}
	//DebugOut(ToWSTR(std::to_string(synergies) + "\n").c_str());
	//coObj->CollisionY(this, nyCollision, 0);
	CGameObject::CollisionY(coObj, nyCollision, Actively);

}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isHidden) return;

	if (fabs(vx + ax * dt) < vxMax) {
		vx = vx + ax * dt;
	}

	if (vx > 0) f = -MARIO_FRICTION;
	if (vx < 0) f = MARIO_FRICTION;
	if (fabs(vx) > fabs(f))
		vx = vx + f;
	else vx = 0;


	vy += MARIO_GRAVITY * dt;

	CGameObject::Update(dt);


	CollisionWithObj(coObjects);

	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	ax = 0;
	movementRatioX = 1;
	vxMax = VELOCITY_X_MAX;
	//DebugOut(ToWSTR(std::to_string(vy) + "\n").c_str());
}

void CMario::Render()
{
	int alpha = 255;
	if (untouchable) alpha = 128;

	LPANIMATION anim = CAnimations::GetInstance()->Get(GetAnimationIdFromState());

	if (anim != NULL)
	{
		if (nx == -1)
			anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f), alpha);
		else
			anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f), alpha);

	}

	RenderBoundingBox();
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
		if (!type)
		{
			SwitchState(EMarioState::JUMP);
		}

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