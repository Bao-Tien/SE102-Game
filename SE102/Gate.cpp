#include "Gate.h"

CGate::CGate(float x, float y, float width, float height, int stt) : CCollisionBox(x, y, width, height)
{
	this->stt = stt + 1;
}
string CGate::GetAnimationFromStt()
{
	switch (stt)
	{
	case 1:
		return GATE_ANI_1;
		break;
	case 2:
		return GATE_ANI_2;
		break;
	case 3:
		return GATE_ANI_3;
		break;
	case 4:
		return GATE_ANI_4;
		break;
	case 5:
		return GATE_ANI_5;
		break;
	case 6:
		return GATE_ANI_6;
		break;
	default:
		break;
	}
}
void CGate::Render()
{
	LPANIMATION anim = CAnimations::GetInstance()->Get(GetAnimationFromStt());
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	//RenderBoundingBox();
}
