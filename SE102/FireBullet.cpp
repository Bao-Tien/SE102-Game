#include "FireBullet.h"
#include "Game.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Enemy.h"

CFireBullet::CFireBullet(int nx, float x, float y) :CGameObject()
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	vy = 0;
	isHidden = true;
}

void CFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_BULLET_WIDTH;
	bottom = y + FIRE_BULLET_HEIGHT;
}

void CFireBullet::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (Actively == 1)
	{
		if (dynamic_cast<CEnemy*>(coObj))
		{
			((CEnemy*)coObj)->SetState(EnemyState::BEING_ATTACKED, -nx);
			SetState(BULLET_STATE_NOACTIVE);
		}
		if (nxCollision != 0) {
			SetState(BULLET_STATE_NOACTIVE);
		}
	}
	
}
void CFireBullet::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 1)
	{
		if (dynamic_cast<CEnemy*>(coObj))
		{
			((CEnemy*)coObj)->SetState(EnemyState::BEING_ATTACKED, -nx);
			SetState(BULLET_STATE_NOACTIVE);
		}
		else if (nyCollision < 0)
			vy = -BULLET_SPEED_Y;
	}
	
}
void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isHidden) return;
	vx = BULLET_SPEED_X  * nx;
	vy += BULLET_GRAVITY * dt;
	CGameObject::Update(dt);
	CollisionWithObj(coObjects);
	if (!this->isInScreen()) this->isHidden = true;
}

void CFireBullet::Render()
{
	LPANIMATION anim = CAnimations::GetInstance()->Get(ANI_FIRE_BULLET);
	if (anim != NULL)
	{
		if (nx < 0)
			anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f));
		else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	}
	RenderBoundingBox();
}

void CFireBullet::SetState(int state, int nx)
{
	switch (state)
	{
	case BULLET_STATE_ACTIVE:
		this->isHidden = false;
		this->nx = nx;
		this->state = state;
		break;
	case BULLET_STATE_NOACTIVE:
		vx = 0;
		this->isHidden = true;
		this->state = state;
		break;
	default:
		break;
	}

}