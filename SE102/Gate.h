#pragma once
#include "CollisionBox.h"

#define GATE_ANI_1               "ani-gate-1"
#define GATE_ANI_2               "ani-gate-2"
#define GATE_ANI_3               "ani-gate-3"
#define GATE_ANI_4               "ani-gate-4"
#define GATE_ANI_5               "ani-gate-5"
#define GATE_ANI_6               "ani-gate-6"
class CGate: public CCollisionBox
{
	int stt;
	virtual void Render();
public:

	CGate(float x, float y, float width, float height, int stt);
	string GetAnimationFromStt();
};

