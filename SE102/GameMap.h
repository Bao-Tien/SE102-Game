#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"
#include "./MapReader/Tmx.h.in"
#include "TextureManager.h"
class GameMap
{
public:
    GameMap(const char* filePath);

    Tmx::Map* GetMap();

    int GetWidth(); // o
    int GetHeight();
    int GetTileWidth(); //pixel
    int GetTileHeight();

    void Draw(D3DXVECTOR2 scale);

    ~GameMap();

private:
    void LoadMap(const char* filePath);

    Tmx::Map* mMap;
    std::map<string, LPDIRECT3DTEXTURE9>          mListTileset;
};

#endif

