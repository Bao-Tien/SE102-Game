#pragma once
#include "Utils.h"
#include "Transform.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "RectF.h"
#include <memory>
#include <unordered_map>
#include "d3dx9.h"

class CTileSet
{
	int firstgid;

	D3DXVECTOR2 tileSize;

	int tileCount;
	int columns;
	std::string name;

	LPDIRECT3DTEXTURE9 texture;

	unordered_map<int, std::shared_ptr<RectF>> blocks;

public:
	CTileSet(int firstgid, D3DXVECTOR2 tileSize, int tileCount, int columns, string imgPath);
	CTileSet(TiXmlElement* data, string xmlPath);

	int GetFirstGID();

	std::shared_ptr<RectF> GetBlockBoundingBox(int id); //lm j  day?

	void Draw(int gid, D3DXVECTOR2 finalPos);

	~CTileSet();
};

typedef CTileSet* LPTileSet;

