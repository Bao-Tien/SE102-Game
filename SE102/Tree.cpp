#include "Tree.h"

CTree::CTree(float x, float y, float width, float height) : CCollisionBox(x, y, width, height)
{
}

void CTree::Render()
{
	LPANIMATION anim = CAnimations::GetInstance()->Get(TREE_ANI);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	//RenderBoundingBox();
}
