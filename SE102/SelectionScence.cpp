#include "SelectionScence.h"
#include "TextureManager.h"
#include <dinput.h>
#include "Game.h"
#include "MarioSelectScence.h"
#include "SelectionScence.h"

CSelectionScence::CSelectionScence(std::string id, std::string filePath) : CScene(id, filePath)
{
	key_handler = new CSelectionScenceKeyHandler(this);
}

bool CSelectionScence::Load()
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
	mMap = CGameMap().FromTMX(MapPath, &objects_Map,&objects_Active, &objects_NoActive);

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
	if (type_Player == "marioSelectionScence") 
		player = new CMarioSelectScence(player_x, player_y);

	

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", sceneFilePath);

}

void CSelectionScence::Unload()
{
	CleanupListObjects(objects_Map);
	player = NULL;
	
}

void CSelectionScence::Update(DWORD dt)
{
	auto a = objects_Map;
	//for (int i = 0; i < objects_Map.size(); i++)
		//player->Update(dt, objects_Map);
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects_Map.size(); i++)
	{
		coObjects.push_back(objects_Map[i]);
	}
	player->Update(dt, &coObjects);
}

void CSelectionScence::Render()
{
	mMap->Render();
	for (int i = 0; i < objects_Map.size(); i++)
	{
		objects_Map[i]->Render();
	}
	for (int i = 0; i < objects_NoActive.size(); i++)
	{
		objects_NoActive[i]->Render();
	}
	player->Render();
}

void CSelectionScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMarioSelectScence* currentPlayer = (CMarioSelectScence*)(((CSelectionScence*)scence)->GetPlayer());
	if (game->IsKeyDown(DIK_RIGHT))
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_LEFT);
	else if (game->IsKeyDown(DIK_UP))
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_DOWN);
	else
	{
		currentPlayer->vx = 0;
		currentPlayer->vy = 0;
	}
		
}
void CSelectionScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMarioSelectScence* currentPlayer = (CMarioSelectScence*)(((CSelectionScence*)scence)->GetPlayer());
	switch (KeyCode)
	{
	case DIK_S:
		CGame::GetInstance()->SwitchScene("1");
		break;
	/*case DIK_RIGHT:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_RIGHT);
		break;
	case DIK_LEFT:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_LEFT);
		break;
	case DIK_UP:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_UP);
		break;
	case DIK_DOWN:
		currentPlayer->KeyboardHandle(KEYBOARD_PRESS_DOWN);
		break;*/
	default:
		currentPlayer->vx = 0;
		currentPlayer->vy = 0;
		break;
	}
}