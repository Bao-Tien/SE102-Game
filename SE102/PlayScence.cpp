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
#include "MarioSmall.h"
#include "MarioBig.h"
#include "MarioRaccoon.h"
#include "MarioFire.h"
#include "Goomba.h"
using namespace std;

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::SwitchPlayer(LPGAMEOBJECT newPlayer)
{
	if (!newPlayer) return;

	if (player)
	{
		float l_old, t_old, r_old, b_old;
		player->GetBoundingBox(l_old, t_old, r_old, b_old);
		float l_new, t_new, r_new, b_new;
		newPlayer->GetBoundingBox(l_new, t_new, r_new, b_new);
		newPlayer->y = player->y + (b_old - t_old) - (b_new - t_new) - 1;
		newPlayer->x = player->x;
	}

	while (objects.size() > 0) {
		delete objects.at(0);
		objects.erase(objects.begin());
	}

	player = newPlayer;
	objects.push_back(newPlayer);

	CGame::GetInstance()->camera->InitPositionController(player);
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

	OutputDebugStringW(ToLPCWSTR("MapPath : " + MapPath + '\n'));

	//load file bbox
	TiXmlElement* bbox = root->FirstChildElement("BBox");
	string BboxPath = bbox->Attribute("path");
	string BboxId = bbox->Attribute("id");
	CTextures::GetInstance()->Initialization(BboxPath, BboxId);

	OutputDebugStringW(ToLPCWSTR("BboxPath : " + BboxPath + '\n'));

	//load texture
	TiXmlElement* textures = root->FirstChildElement("Textures");
	for (TiXmlElement* node = textures->FirstChildElement("Texture"); node != nullptr; node = node->NextSiblingElement("Texture"))
	{
		string TexturePath = node->Attribute("path");
		string TextureId = node->Attribute("id");
		CTextures::GetInstance()->Initialization(TexturePath, TextureId);
	}

	//load Sprite
	TiXmlElement* sprites = root->FirstChildElement("Sprites");
	for (TiXmlElement* node = sprites->FirstChildElement("Sprite"); node != nullptr; node = node->NextSiblingElement("Sprite"))
	{
		string SpritePath = node->Attribute("path");
		CSprites::GetInstance()->Initialization(SpritePath);
	}
	

	//load Animation
	TiXmlElement* animations = root->FirstChildElement("Animations");
	for (TiXmlElement* node = animations->FirstChildElement("Animation"); node != nullptr; node = node->NextSiblingElement("Animation"))
	{
		string AnimationPath = node->Attribute("path");
		CAnimations::GetInstance()->Initialization(AnimationPath);
	}
	

	//load player
	TiXmlElement* play = root->FirstChildElement("Player");
	string type_Player = play->Attribute("type");
	float player_x = atof(play->Attribute("x"));
	float player_y = atof(play->Attribute("y"));
	if (type_Player == "marioSmall") SwitchPlayer(new CMarioSmall(player_x, player_y));
	else if (type_Player == "marioBig") SwitchPlayer(new CMarioBig(player_x, player_y));
	else if (type_Player == "marioRaccoon") SwitchPlayer(new CMarioRaccoon(player_x, player_y));
	else if (type_Player == "marioFire") SwitchPlayer(new CMarioFire(player_x, player_y));

	//load object (Goomba)
	TiXmlElement* objects = root->FirstChildElement("Objects");
	for (TiXmlElement* node = objects->FirstChildElement("Goomba"); node != nullptr; node = node->NextSiblingElement("Goomba"))
	{
		float goomba_x = atof(node->Attribute("x"));
		float goomba_y = atof(node->Attribute("y"));
		LPGAMEOBJECT goomba = new CGoomba(goomba_x, goomba_y);
		objects_Enemy.push_back(goomba);
	}


	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", sceneFilePath);
	mMap = CGameMap().FromTMX(MapPath, &objects_Map);
}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects_Map.size(); i++)
	{
		coObjects.push_back(objects_Map[i]);
	}

	if (player->x - CGame::GetInstance()->camera->GetCamPosition().x < CGame::GetInstance()->GetScreenWidth() / 2)
	{
		for (int i = 0; i < objects_Enemy.size(); i++)
		{
			if (!objects_Enemy[i]->isHidden)
			{
				objects_Enemy[i]->Update(dt, &coObjects);
			}
		}
	}

	for (size_t i = 0; i < objects_Enemy.size(); i++)
	{
		coObjects.push_back(objects_Enemy[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	

	CGame::GetInstance()->camera->Update(dt);

	if (player == NULL) return;

}

void CPlayScene::Render()
{
	mMap->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->isHidden)
			objects[i]->Render();
	}
	for (int i = 0; i < objects_Map.size(); i++)
	{
		if (!objects_Map[i]->isHidden)
			objects_Map[i]->Render();
	}
	for (int i = 0; i < objects_Enemy.size(); i++)
	{
		/*if (!objects_Enemy[i]->isHidden)
		{
			objects_Enemy[i]->Render();
		}*/
		objects_Enemy[i]->Render();
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

	CMario* currentPlayer = (CMario*)((CPlayScene*)scence)->GetPlayer();

	switch (KeyCode)
	{
	case DIK_1:
		((CPlayScene*)scence)->SwitchPlayer(new CMarioSmall(currentPlayer->x, currentPlayer->y));
		break;
	case DIK_2:
		((CPlayScene*)scence)->SwitchPlayer(new CMarioBig(currentPlayer->x, currentPlayer->y));
		break;
	case DIK_3:
		((CPlayScene*)scence)->SwitchPlayer(new CMarioFire(currentPlayer->x, currentPlayer->y));
		break;
	case DIK_4:
		((CPlayScene*)scence)->SwitchPlayer(new CMarioRaccoon(currentPlayer->x, currentPlayer->y));
		break;
		/*case DIK_4:
		mario->SetLevel(MARIO_LEVEL_FROG);
		break;*/
	/*case DIK_5:
		((CPlayScene*)scence)->SwitchPlayer(new CMarioFire(currentPlayer->x, currentPlayer->y));
		break;*/
	/*case DIK_6:
		currentPlayer->SetLevel(MARIO_LEVEL_TANOOKI);
		break;
	case DIK_7:
		currentPlayer->SetLevel(MARIO_LEVEL_HAMMER);
		break;*/
	case DIK_X:
		currentPlayer->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_S:
		currentPlayer->SetState(MARIO_STATE_HIGH_JUMP);
		break;
	case DIK_D:
		currentPlayer->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_B:
		currentPlayer->SetState(MARIO_STATE_FLY);
		break;
	case DIK_R:
		currentPlayer->Reset();
		break;
		
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	LPGAMEOBJECT mario = ((CPlayScene*)scence)->GetPlayer();

	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUN_RIGHT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else 
		if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUN_LEFT);
			else mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		

	else
		mario->SetState(MARIO_STATE_IDLE);
}