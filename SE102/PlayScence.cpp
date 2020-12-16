#include <iostream>
#include <fstream>
#include <algorithm>

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
#include "Koopas.h"
#include "QuestionBrick.h"
#include "Red_Goomba.h"
#include "Para_Goomba.h"
#include "MagicObject.h"
using namespace std;

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::AddObjToObjects_Magic(LPGAMEOBJECT a)
{
	objects_Magic.push_back(a);
}
void CPlayScene::AddObjToObjects_Enemy(LPGAMEOBJECT a)
{
	objects_Enemy.push_back(a);
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
	mMap = CGameMap().FromTMX(MapPath, &objects_Map, &objects_Active);

	//load file bbox
	TiXmlElement* bbox = root->FirstChildElement("BBox");
	string BboxPath = bbox->Attribute("path");
	string BboxId = bbox->Attribute("id");
	TiXmlElement* BackgroundColor_bbox = bbox->FirstChildElement("BackgroundColor");
	int bbox_R = atoi(BackgroundColor_bbox->Attribute("R"));
	int bbox_G = atoi(BackgroundColor_bbox->Attribute("G"));
	int bbox_B = atoi(BackgroundColor_bbox->Attribute("B"));
	CTextures::GetInstance()->Initialization(BboxPath, BboxId, D3DCOLOR_XRGB(bbox_R, bbox_G, bbox_B));

	OutputDebugStringW(ToLPCWSTR("BboxPath : " + BboxPath + '\n'));

	//load texture
	TiXmlElement* textures = root->FirstChildElement("Textures");
	for (TiXmlElement* node = textures->FirstChildElement("Texture"); node != nullptr; node = node->NextSiblingElement("Texture"))
	{
		string TexturePath = node->Attribute("path");
		string TextureId = node->Attribute("id");
		CTextures::GetInstance()->Initialization(TexturePath, TextureId, D3DCOLOR());
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
	// (Koopas)
	for (TiXmlElement* node = objects->FirstChildElement("Koopas"); node != nullptr; node = node->NextSiblingElement("Koopas"))
	{
		float koopas_x = atof(node->Attribute("x"));
		float koopas_y = atof(node->Attribute("y"));
		LPGAMEOBJECT koopas = new CKoopas(koopas_x, koopas_y);
		objects_Enemy.push_back(koopas);
	}
	// (Para_Goomba)
	for (TiXmlElement* node = objects->FirstChildElement("Para_Goomba"); node != nullptr; node = node->NextSiblingElement("Para_Goomba"))
	{
		float para_x = atof(node->Attribute("x"));
		float para_y = atof(node->Attribute("y"));
		LPGAMEOBJECT para = new CPara_Goomba(para_x, para_y);
		objects_Enemy.push_back(para);
	}
	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", sceneFilePath);
	
}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects_Map.size(); i++)
	{
		coObjects.push_back(objects_Map[i]);
	}
	

	for (int i = 0; i < objects_Enemy.size(); i++)
	{
		if (!objects_Enemy[i]->isHidden)
		{
			objects_Enemy[i]->Update(dt, &coObjects);
		}
	}

	
	for (int i = 0; i < objects_Active.size(); i++)
	{
		objects_Active[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < objects_Active.size(); i++)
	{
		coObjects.push_back(objects_Active[i]);
	}
	for (int i = 0; i < objects_Magic.size(); i++)
	{
		objects_Magic[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < objects_Magic.size(); i++)
	{
		coObjects.push_back(objects_Magic[i]);
	}
	for (size_t i = 0; i < objects_Enemy.size(); i++)
	{
		coObjects.push_back(objects_Enemy[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (((CMario*)player)->mState == EMarioState::REMEMBER) {
			SwitchPlayer(new CMarioSmall(((CMario*)player)->x, ((CMario*)player)->y));
		}
			
		objects[i]->Update(dt, &coObjects);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	CGame::GetInstance()->camera->Update(dt);
	

	if (player == NULL) return;

}

void CPlayScene::Render()
{
	
	for (int i = 0; i < objects_Map.size(); i++)
	{
		if (!objects_Map[i]->isHidden)
			objects_Map[i]->Render();
	}
	
	mMap->Render();
	for (int i = 0; i < objects_Enemy.size(); i++)
	{
		if (!objects_Enemy[i]->isHidden)
			objects_Enemy[i]->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->isHidden)
			objects[i]->Render();
	}
	for (int i = 0; i < objects_Magic.size(); i++)
	{
		if (!objects_Magic[i]->isHidden)
			objects_Magic[i]->Render();
	}
	for (int i = 0; i < objects_Active.size(); i++)
	{
		if (!objects_Active[i]->isHidden)
			objects_Active[i]->Render();
	}
	
	

}

void CPlayScene::Unload()
{
	CleanupListObjects(objects);
	CleanupListObjects(objects_Active);
	CleanupListObjects(objects_Map);
	CleanupListObjects(objects_Enemy);
	CleanupListObjects(objects_Magic);


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
	case DIK_X:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_X,	false);
		break;
	case DIK_S: 
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_S, false);
		break;
	case DIK_A:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_A, false);
		break;
	case DIK_R:
		currentPlayer->Reset();
		break;
		
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* currentPlayer = (CMario*)(((CPlayScene*)scence)->GetPlayer());

	if (currentPlayer->mState == EMarioState::DIE) return;
	// Su kien di kem
	if (game->IsKeyDown(DIK_A))//chay nhanh
	{
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_A, true);
	}

	// Su kien rieng
	if (game->IsKeyDown(DIK_RIGHT))
	{
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_RIGHT, true);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_LEFT, true);
	}
	else if (game->IsKeyDown(DIK_S))
	{
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_S, true);
	}
}