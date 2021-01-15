#pragma once
#include "Green_Koopas.h"

class CGreen_Paratroopa : public CGreen_Koopas
{
public:
	CGreen_Paratroopa(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
};

