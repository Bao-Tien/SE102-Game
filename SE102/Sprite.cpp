#include "Sprite.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, Vector2 pivot)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->pivot = pivot;
}


void CSprite::Draw(float x, float y, D3DXVECTOR2 scale, int alpha)
{
	CGame* game = CGame::GetInstance();
	if (scale.x == -1.0f) {
		game->Draw(x, y, texture, left, top, right, bottom, scale, alpha);
	}
	else {
		game->Draw(x, y, texture, left, top, right, bottom, scale, alpha, pivot);
	}
	
}
