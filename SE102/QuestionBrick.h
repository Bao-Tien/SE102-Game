#pragma once
#include "CollisionBox.h"

#define QUESTIONBRICK_STATE_AFTER_COLLISION 230
#define QUESTIONBRICK_STATE_NORMAL 231

#define QUESTIONBRICK_SPEED_Y 0.25f
#define QUESTIONBRICK_GRAVITY 0.006f

#define QUESTIONBRICK_ANI_NORMAL               "ani-question-block"
#define QUESTIONBRICK_ANI_AFTER_COLLISION      "ani-empty-block"

#define QUESTIONBRICK_X1    720
#define QUESTIONBRICK_X2    1968
#define QUESTIONBRICK_X3    4272
#define QUESTIONBRICK_X4    4368


class CQuestionBrick : public CCollisionBox
{
private:
	int state;
	float yStart;
	bool hasCollided;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CQuestionBrick(float x, float y, float width, float height);
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override ;
	void SetState(int state);
	void SetMagicObject();
};

