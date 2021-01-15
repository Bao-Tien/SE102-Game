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
#include "Red_Venus.h"
#include "Bullet_Venus.h"
#include "SpriteManager.h"
#include "PlayScenceConst.h"
#include "Green_Venus.h"
#include "Piranha_Plant.h"
#include "Green_Koopas.h"
#include "Green_Paratroopa.h"

using namespace std;

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	sceneTime = 600000;
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
	mMap = CGameMap().FromTMX(MapPath, &objects_Map, &objects_Active, NULL, &objects_Brick);

	//load texture
	TiXmlElement* textures = root->FirstChildElement("Textures");
	for (TiXmlElement* node = textures->FirstChildElement("Texture"); node != nullptr; node = node->NextSiblingElement("Texture"))
	{
		string TexturePath = node->Attribute("path");
		string TextureId = node->Attribute("id");
		auto TranColorR = node->Attribute("tranColorR");
		auto TranColorG = node->Attribute("tranColorG");
		auto TranColorB = node->Attribute("tranColorB");

		if (TranColorR != NULL && TranColorG != NULL && TranColorB != NULL) {

			CTextures::GetInstance()->Initialization(TexturePath, TextureId, D3DCOLOR_XRGB(atoi(TranColorR), atoi(TranColorG), atoi(TranColorB)));
		}
		else {
			CTextures::GetInstance()->Initialization(TexturePath, TextureId, D3DCOLOR());
		}
		
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
	// (Para_Goomba)
	for (TiXmlElement* node = objects->FirstChildElement("Green_Paratroopa"); node != nullptr; node = node->NextSiblingElement("Green_Paratroopa"))
	{
		float paratroopa_x = atof(node->Attribute("x"));
		float paratroopa_y = atof(node->Attribute("y"));
		LPGAMEOBJECT paratroopa = new CGreen_Paratroopa(paratroopa_x, paratroopa_y);
		objects_Enemy.push_back(paratroopa);
	}
	//Red_Venus
	for (TiXmlElement* node = objects->FirstChildElement("Red_Venus"); node != nullptr; node = node->NextSiblingElement("Red_Venus"))
	{
		float RedVenus_x = atof(node->Attribute("x"));
		float RedVenus_y = atof(node->Attribute("y"));
		LPGAMEOBJECT redVenus = new CRed_Venus(RedVenus_x, RedVenus_y);
		LPGAMEOBJECT bullet = ((CRed_Venus*)redVenus)->GetBullet();
		objects_Active.push_back(redVenus); 
		onlyRender.push_back(bullet);
	}
	//Green_Venus
	for (TiXmlElement* node = objects->FirstChildElement("Green_Venus"); node != nullptr; node = node->NextSiblingElement("Green_Venus"))
	{
		float GreenVenus_x = atof(node->Attribute("x"));
		float GreenVenus_y = atof(node->Attribute("y"));
		LPGAMEOBJECT greenVenus = new CGreen_Venus(GreenVenus_x, GreenVenus_y);
		LPGAMEOBJECT bullet = ((CGreen_Venus*)greenVenus)->GetBullet();
		objects_Active.push_back(greenVenus);
		onlyRender.push_back(bullet);
	}
	//Piranha_Plant
	for (TiXmlElement* node = objects->FirstChildElement("Piranha_Plant"); node != nullptr; node = node->NextSiblingElement("Piranha_Plant"))
	{
		float Piranha_x = atof(node->Attribute("x"));
		float Piranha_y = atof(node->Attribute("y"));
		LPGAMEOBJECT piranha = new CPiranha_Plant(Piranha_x, Piranha_y);
		objects_Active.push_back(piranha);
	}
	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", sceneFilePath);
	
}

void CPlayScene::Update(DWORD dt)
{
	
	sceneTime -= dt;
	if (sceneTime < 0) {
		sceneTime = 0;
		// Xu ly viec het thoi gian..
	}
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects_Map.size(); i++)
	{
		coObjects.push_back(objects_Map[i]);
	}

	for (int i = 0; i < objects_Brick.size(); i++)
	{
		objects_Brick[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < objects_Brick.size(); i++)
	{
		coObjects.push_back(objects_Brick[i]);
	}

	for (int i = 0; i < objects_Enemy.size(); i++)
	{
		if (!objects_Enemy[i]->isHidden)
		{
			if(objects_Enemy[i]->isInScreen())
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

	synergies = int(sceneSynergies * 6 / 1000);
}

void CPlayScene::DrawChangeStringToSprite(string input, Vector2 position)
{
	for (int i = 0; i < input.length(); i++)
	{
		string aniId = string(1, input[i]) == " " ? "spr-font-space" : "spr-font-" + string(1, input[i]);
		CSprites::GetInstance()->Get(aniId)->DrawWithoutConverting(position.x + i * 20, position.y);
	}
}
void CPlayScene::DrawFixedLengthNumber(std::string inp, Vector2 position, char defaultChar, int numLength) {
	while (inp.length() < numLength) inp = string(1, defaultChar) + inp;
	for (int i = 0; i < inp.length(); i++) {
		CSprites::GetInstance()->Get("spr-font-" + string(1, inp[i]))->DrawWithoutConverting(position.x + i * 20, position.y);
	}
}
void CPlayScene::DrawFollow(string inp1, int x1, string inp2, int x2, Vector2 position)
{
	for (int i = 0; i < x1; i++)
		CSprites::GetInstance()->Get(inp1)->DrawWithoutConverting(position.x + i * 20, position.y);
	for (int i = x1; i < x1 + x2; i++)
		CSprites::GetInstance()->Get(inp2)->DrawWithoutConverting(position.x + i * 20, position.y);
}

void CPlayScene::Render_HUD()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 black = CTextures::GetInstance()->Get(BLACK_ID);

	rect.left = 0;
	rect.top = 0;
	rect.right = SCREEN_HEIGHT;
	rect.bottom = HUD_HEIGHT;

	Vector2 posHUD = Vector2(0, SCREEN_HEIGHT - HUD_HEIGHT);
	//player
	CGame::GetInstance()->DrawWithoutConverting(posHUD.x, posHUD.y, black, rect.left, rect.top, rect.right, rect.bottom);
	CSprites::GetInstance()->Get(HUD_ANI)->DrawWithoutConverting(posHUD.x + 20, posHUD.y + 20);
	//sceneSynergies
	
	DrawFollow(ARROW_WHITE_ANI, synergies, ARROW_BLACK_ANI, 6 - synergies, Vector2(posHUD.x + 180, posHUD.y + 41));
	if(synergies==6)
		CSprites::GetInstance()->Get(P_ANI)->DrawWithoutConverting(posHUD.x + 300, posHUD.y + 41);
	else CSprites::GetInstance()->Get(P_BLACK_ANI)->DrawWithoutConverting(posHUD.x + 300, posHUD.y + 41);

	//00000000 diem
	DrawFixedLengthNumber(to_string(scenePoint), Vector2(posHUD.x + 180, posHUD.y + 69), '0', 8);
	//tg=300
	DrawChangeStringToSprite(to_string((sceneTime / 1000)), Vector2(posHUD.x + 400, posHUD.y + 69));
	
	CSprites::GetInstance()->Get(EMPTY_CARD_ANI)->DrawWithoutConverting(posHUD.x + 600, posHUD.y + 20);
	CSprites::GetInstance()->Get(EMPTY_CARD_ANI)->DrawWithoutConverting(posHUD.x + 700, posHUD.y + 20);
	CSprites::GetInstance()->Get(EMPTY_CARD_ANI)->DrawWithoutConverting(posHUD.x + 800, posHUD.y + 20);
}

void CPlayScene::Render()
{
	
	for (int i = 0; i < objects_Map.size(); i++)
	{
		if (!objects_Map[i]->isHidden)
			objects_Map[i]->Render();
	}
	for (int i = 0; i < objects_Active.size(); i++)
	{
		if (!objects_Active[i]->isHidden)
			objects_Active[i]->Render();
	}
	mMap->Render();
	for (int i = 0; i < objects_Brick.size(); i++)
	{
		if (!objects_Brick[i]->isHidden)
			objects_Brick[i]->Render();
	}
	for (int i = 0; i < onlyRender.size(); i++)
	{
		if (!onlyRender[i]->isHidden)
			onlyRender[i]->Render();
	}
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
	Render_HUD();
}

void CPlayScene::Unload()
{
	CleanupListObjects(objects);
	CleanupListObjects(objects_Active);
	CleanupListObjects(objects_Brick);
	CleanupListObjects(objects_Map);
	CleanupListObjects(objects_Enemy);
	CleanupListObjects(objects_Magic);
	CleanupListObjects(onlyRender);

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