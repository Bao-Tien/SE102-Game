#pragma once
#include "Sprite.h";
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "tinystr.h"
#include "tinyxml.h"

/*
	Manage sprite database
*/

class CSprites
{
	static CSprites* __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 pivot = D3DXVECTOR2(0,0));
	LPSPRITE Get(string id);
	void Clear();
	void Initialization(string path);
	bool LoadSpriteFile(string path);
	static CSprites* GetInstance();
};