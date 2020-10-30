#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Transform.h"

class CMapLayer
{
private:
	int id;
	int width;
	int height;

	int** tiles;

public:
	CMapLayer();
	~CMapLayer();

	CMapLayer(TiXmlElement* data);

	bool Hidden = false;

	int GetTileID(int x, int y);


};

