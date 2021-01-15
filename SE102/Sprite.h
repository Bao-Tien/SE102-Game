#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Transform.h"
using namespace std;

class CSprite
{
	string id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;
	Vector2 pivot;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, Vector2 pivot = Vector2(0,0));

	void Draw(float x, float y, D3DXVECTOR2 scale = Vector2(1,1), int alpha = 255);
	void DrawWithoutConverting(float x, float y, D3DXVECTOR2 scale = Vector2(1, 1), int alpha = 255);
};

typedef CSprite* LPSPRITE;
