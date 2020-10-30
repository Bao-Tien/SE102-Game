#include "GameMap.h"
#include "Utils.h"
#include <string>

GameMap::GameMap(const char* filePath)
{
    LoadMap(filePath);
}

GameMap::~GameMap()
{
    delete mMap;
}

void GameMap::LoadMap(const char* filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        string idTex = "1999" + std::to_string(i);
        const Tmx::Tileset* tileset = mMap->GetTileset(i);
        // Doc Texture
        CTextures::GetInstance()->Add(idTex, ToLPCWSTR(tileset->GetImage()->GetSource().c_str()), D3DCOLOR_XRGB(255, 128, 192));

        mListTileset.insert(std::pair<string, LPDIRECT3DTEXTURE9>(idTex, CTextures::GetInstance()->Get(idTex))); // lay dc listTexture

    }
}

Tmx::Map* GameMap::GetMap()
{
    return mMap;
}

int GameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

void GameMap::Draw(D3DXVECTOR2 scale)
{
    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        RECT sourceRECT;

        


        for (size_t m = 0; m < layer->GetHeight(); m++)
        {
            for (size_t n = 0; n < layer->GetWidth(); n++)
            {
                int tilesetIndex = layer->GetTileTilesetIndex(n, m);

                if (tilesetIndex != -1)
                {
                    const Tmx::Tileset* tileSet = mMap->GetTileset(tilesetIndex);
                    
                    int tileWidth = mMap->GetTileWidth();
                    int tileHeight = mMap->GetTileHeight();

                    int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                    int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;


                    LPDIRECT3DTEXTURE9 tex = mListTileset["1999"+ std::to_string(layer->GetTileTilesetIndex(n, m))];

                    //tile index
                    int tileID = layer->GetTileId(n, m);

                    int y = tileID / tileSetWidth; //32/29
                    int x = tileID - y * tileSetWidth;

                    sourceRECT.top = y * tileHeight;
                    sourceRECT.bottom = sourceRECT.top + tileHeight;
                    sourceRECT.left = x * tileWidth;
                    sourceRECT.right = sourceRECT.left + tileWidth;

                    //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                    //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);

                    //D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                    /*sprite->SetWidth(tileWidth);
                    sprite->SetHeight(tileHeight);*/
                    tex;
                    /*sprite->Draw(position, sourceRECT, D3DXVECTOR2(), D3DXVECTOR2(), 0.0f, D3DXVECTOR2(), D3DCOLOR_XRGB(255, 128, 192));
                */
                    CSprite("9", sourceRECT.left, sourceRECT.top, sourceRECT.right, sourceRECT.bottom, tex)
                        .Draw(50, 1200,scale, 255);


                }
            }
        }
    }
}