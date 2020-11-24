#include "Koopas.h"
#include "ScenceManager.h"
#include "Game.h"
#include "Mario.h"
#include "MarioConst.h"
#include "PlayScence.h"

CKoopas::CKoopas(float x, float y)
{
	this->x = x;
	this->y = y;
	this->isHidden = false;
	
	SetState(KOOPAS_STATE_LIVE);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_COUCH || state == KOOPAS_STATE_BEING_SHOOTED|| state == KOOPAS_STATE_BEING_HELD|| state == KOOPAS_STATE_HELD)
		bottom = y + KOOPAS_BBOX_HEIGHT_COUCH;
	else if (state == KOOPAS_STATE_BEING_ATTACK || state == KOOPAS_STATE_DIE)
		left = top = right = bottom = 0;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::NoCollision()
{
	CGameObject::NoCollision();
}
void CKoopas::CollisionX(LPGAMEOBJECT coObj, int nxCollition)
{
		if (dynamic_cast<CMario*>(coObj))
		{
			CMario* mario = (CMario*)coObj;
			if (state != KOOPAS_STATE_DIE)
			{
				if (mario->mState == EMarioState::ATTACK)
				{
					SetState(KOOPAS_STATE_BEING_ATTACK, nx); //quay duoi//ban
				}
				else if (mario->vxMax == VELOCITY_X_SPEEDUP_MAX) //nhan nut A
				{
					if (state == KOOPAS_STATE_COUCH)
					{
						mario->SwitchState(EMarioState::HOLD);
						SetState(KOOPAS_STATE_BEING_HELD, nx);
					}
				}
				else if (mario->mState == EMarioState::WALK)
				{
					if (state != KOOPAS_STATE_LIVE)
					{
						SetState(KOOPAS_STATE_BEING_ATTACK, nx);//bi da
					}
				}
			}
		}
		else {
			vx = -vx;
			this->nx = -this->nx;
		}
}
void CKoopas::CollisionY(LPGAMEOBJECT coObj, int nyCollition)
{
	
	/*if (state == KOOPAS_STATE_BEING_ATTACK)
	{
		SetState(KOOPAS_STATE_DIE);
	}*/
	if (nyCollition < 0)
	{
		if (dynamic_cast<CMario*>(coObj))
		{
			if (state != KOOPAS_STATE_COUCH)
			{
				SetState(KOOPAS_STATE_COUCH); //nup
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else vy = 0;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += KOOPAS_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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
			if (state != KOOPAS_STATE_HELD)
			{
				vx = -vx;
				this->nx = -this->nx;
			}
		}

		if (ny < 0) {
			vy = 0;
			if (state == KOOPAS_STATE_BEING_ATTACK)
			{
				SetState(KOOPAS_STATE_DIE);
			}
		}
		
	}*/
	if (state == KOOPAS_STATE_COUCH && GetTickCount() - beginState > 500000)
	{
		SetState(KOOPAS_STATE_LIVE);
		y += KOOPAS_BBOX_HEIGHT_COUCH - KOOPAS_BBOX_HEIGHT;
	}
	/*if (state == KOOPAS_STATE_BEING_SHOOTED && GetTickCount() - beginState > 3000)
	{
		SetState(KOOPAS_STATE_DIE);
		this->isHidden = true;
	}*/
	
	if (state == KOOPAS_STATE_BEING_HELD)
	{
		LPGAMEOBJECT player = CScences::GetInstance()->Get(CGame::GetInstance()->GetCurrentSceneId())->GetPlayer();
		if (player->GetvxMax() == VELOCITY_X_SPEEDUP_MAX) { //nhan A
			float l, t, r, b;
			player->GetBoundingBox(l, t, r, b);
			int nxPlayer = player->nx;
			if (nxPlayer == 1)
				x = player->x + (r - l);
			else
				x = player->x - KOOPAS_BBOX_WIDTH;
			y = (player->y + KOOPAS_BBOX_HEIGHT_COUCH / 3);
		}
		else
			SetState(KOOPAS_STATE_DIE);
	}	
}

void CKoopas::Render()
{
	string ani = KOOPAS_ANI_WALKING;
	LPANIMATION anim = CAnimations::GetInstance()->Get(KOOPAS_ANI_WALKING);
	if (!this->isHidden) {
		if (state == KOOPAS_STATE_COUCH || state == KOOPAS_STATE_BEING_SHOOTED|| state== KOOPAS_STATE_BEING_HELD) {
			ani = KOOPAS_ANI_COUCH;
			CAnimations::GetInstance()->Get(ani)->Render(x,y);
			
		}
		else if (state == KOOPAS_STATE_BEING_ATTACK || state == KOOPAS_STATE_DIE)
		{
			ani = KOOPAS_ANI_COUCH;
			LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
			if (anim != NULL)
				anim->Render(x, y, D3DXVECTOR2(1.0f, -1.0f));
		}
		else
		{
			anim = CAnimations::GetInstance()->Get(ani);
			if (anim != NULL)
				if (nx == 1)
					anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f));
				else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
		}
	}


	//RenderBoundingBox();
}

void CKoopas::SetState(int state, float nxCollision)
{
	switch (state)
	{
	case KOOPAS_STATE_COUCH: //nhay len dau 
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_COUCH;
		vx = 0;
		vy = 0;
		beginState = GetTickCount();
		this->state = state;
		break;
	case KOOPAS_STATE_LIVE:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		this->state = state;
		break;
	case KOOPAS_STATE_BEING_ATTACK: // bi quay duoi // bi ban
		if (nxCollision < 0)
		{
			vx = KOOPAS_BEING_SHOOTED_SPEED_X;
		}
		else vx = -KOOPAS_BEING_SHOOTED_SPEED_X;
		vy = -KOOPAS_BEING_SHOOTED_SPEED_Y;
		//beginState = GetTickCount();
		this->state = state;
		break;
	//case KOOPAS_STATE_BEING_SHOOTED: //bi ban
	//	if (nxCollision < 0)
	//	{
	//		vx = KOOPAS_BEING_SHOOTED_SPEED_X;
	//	}
	//	else vx = -KOOPAS_BEING_SHOOTED_SPEED_X;
	//	//beginState = GetTickCount();
	//	this->state = state;
	//	break;
	case KOOPAS_STATE_BEING_HELD:
		this->state = state;
		break;
	//case KOOPAS_STATE_HELD:
		/*if (nxCollision < 0)
		{
			vx = KOOPAS_BEING_SHOOTED_SPEED_X;
		}
		else vx = -KOOPAS_BEING_SHOOTED_SPEED_X;*/
		/*this->state = state;
		break;*/
	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		this->state = state;
		break;
	}

}