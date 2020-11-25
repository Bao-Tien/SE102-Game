#pragma once
#include "CollisionBox.h"

#define QUESTIONBRICK_STATE_AFTER_COLLISION 230
#define QUESTIONBRICK_STATE_NORMAL 231

#define QUESTIONBRICK_SPEED_Y 0.25f
#define QUESTIONBRICK_GRAVITY 0.006f

#define QUESTIONBRICK_ANI_NORMAL               "ani-question-block"
#define QUESTIONBRICK_ANI_AFTER_COLLISION      "ani-empty-block"


class CQuestionBrick : public CCollisionBox
{
private:
	int state;
	float yStart, yEnd;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	
	CQuestionBrick(float x, float y, float width, float height);
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override ;
	void SetState(int state);
};

