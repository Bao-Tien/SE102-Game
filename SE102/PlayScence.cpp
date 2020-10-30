#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "Portal.h"
#include "CollisionBox.h"
#include "ScenceManager.h"
#include "GameObject.h"

using namespace std;

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

bool CPlayScene::Load()
{
	TiXmlDocument document(sceneFilePath.c_str());
	if (!document.LoadFile())
	{
		OutputDebugStringW(ToLPCWSTR(document.ErrorDesc()));
		return false;
	}

	TiXmlElement* root = document.RootElement();

	//load filemap
	TiXmlElement* map = root->FirstChildElement("Map");
	string MapPath = map->Attribute("path");

	/*TiXmlElement* BackgroundColor_map = map->FirstChildElement("BackgroundColor");
	int map_R = atoi(BackgroundColor_map->Attribute("R"));
	int map_G = atoi(BackgroundColor_map->Attribute("G"));
	int map_B = atoi(BackgroundColor_map->Attribute("B"));*/

	OutputDebugStringW(ToLPCWSTR("MapPath : " + MapPath + '\n'));

	//load file bbox
	TiXmlElement* bbox = root->FirstChildElement("BBox");
	string BboxPath = bbox->Attribute("path");
	string BboxId = bbox->Attribute("id");

	TiXmlElement* BackgroundColor_bbox = bbox->FirstChildElement("BackgroundColor");
	int bbox_R = atoi(BackgroundColor_bbox->Attribute("R"));
	int bbox_G = atoi(BackgroundColor_bbox->Attribute("G"));
	int bbox_B = atoi(BackgroundColor_bbox->Attribute("B"));

	OutputDebugStringW(ToLPCWSTR("BboxPath : " + BboxPath + '\n'));

	//load texture
	TiXmlElement* texture = root->FirstChildElement("Texture");
	string TexturePath = texture->Attribute("path");
	string TextureId = texture->Attribute("id");

	TiXmlElement* BackgroundColor_tex = texture->FirstChildElement("BackgroundColor");
	int tex_R = atoi(BackgroundColor_tex->Attribute("R"));
	int tex_G = atoi(BackgroundColor_tex->Attribute("G"));
	int tex_B = atoi(BackgroundColor_tex->Attribute("B"));

	//load Sprite
	TiXmlElement* sprite = root->FirstChildElement("Sprite");
	string SpritePath = sprite->Attribute("path");

	//load Animation
	TiXmlElement* animation = root->FirstChildElement("Animation");
	string AnimationPath = animation->Attribute("path");

	//load player
	TiXmlElement* play = root->FirstChildElement("Player");
	float player_x = atof(play->Attribute("x"));
	float player_y = atof(play->Attribute("y"));

	TiXmlElement* BackgroundColor_play = play->FirstChildElement("BackgroundColor");
	int player_R = atoi(BackgroundColor_play->Attribute("R"));
	int player_G = atoi(BackgroundColor_play->Attribute("G"));
	int player_B = atoi(BackgroundColor_play->Attribute("B"));

	//load Camara
	TiXmlElement* camara = root->FirstChildElement("Camera");
	int start = atoi(camara->Attribute("start"));
	int main = atoi(camara->Attribute("main"));

	TiXmlElement* boundary = camara->FirstChildElement("Boundary");
	int id = atoi(boundary->Attribute("id"));
	int camara_x = atoi(boundary->Attribute("x"));
	int camara_y = atoi(boundary->Attribute("y"));
	int left = atoi(boundary->Attribute("left"));
	int top = atoi(boundary->Attribute("top"));
	int right = atoi(boundary->Attribute("right"));
	int bottom = atoi(boundary->Attribute("bottom"));

	//load BBox
	//load trang thai, thong so mario

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", sceneFilePath);
	//mMap = new CGameMap(MapPath.c_str());
	CTextures::GetInstance()->Initialization(BboxPath, BboxId, bbox_R, bbox_G, bbox_B);
	CTextures::GetInstance()->Initialization(TexturePath, TextureId, tex_R, tex_G, tex_B);
	CSprites::GetInstance()->Initialization(SpritePath);
	CAnimations::GetInstance()->Initialization(AnimationPath);

	CMario* mario = new CMario(50, 1100);
	player = mario;
	objects.push_back(mario);
	CGame::GetInstance()->camera->InitPositionController(player);
	mMap = CGameMap().FromTMX(MapPath, &objects);
	//mMap->GetMapSize(mapSize);
	//CGame::GetInstance()->camera->LoadMap(, &objects);
	//mMap = (new CGameMap())->FromTMX(MapPath, &objects);

	
	//DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	
	//mMap->UpdateCamPosition(camPosition);
	//CGame::GetInstance()->camera->Update(dt);

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	/*for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}*/

	player->Update(dt, &coObjects);
	CGame::GetInstance()->camera->Update(dt);
	mMap->Update(dt);
	//// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	//// Update camera to follow mario
	float cx, cy;
	//player->GetPosition(cx, cy);

	//CGame* game = CGame::GetInstance();
	//cx -= game->GetScreenWidth() / 2;
	//cy -= game->GetScreenHeight() / 2;

	//CGame::GetInstance()->SetCamPos(cx, 1000 /*cy*/);
}

void CPlayScene::Render()
{
	mMap->Render();
	//CGame::GetInstance()->camera->Render();
	float x, y;
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f,1.0f);
	//mMap->Draw(scale);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
		objects[i]->GetPosition(x, y);

	}
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)  //event
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	/*case DIK_4:
		mario->SetLevel(MARIO_LEVEL_FROG);
		break;*/
	case DIK_5:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_6:
		mario->SetLevel(MARIO_LEVEL_TANOOKI);
		break;
	case DIK_7:
		mario->SetLevel(MARIO_LEVEL_HAMMER);
		break;
	case DIK_X:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_HIGH_JUMP);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_R:
		mario->Reset();
		break;
		
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUN_RIGHT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUN_LEFT);
		else mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_S) && game->IsKeyDown(DIK_B))
	{
		mario->SetState(MARIO_STATE_FLY);
	}

	else
		mario->SetState(MARIO_STATE_IDLE);
}