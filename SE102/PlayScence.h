#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "GameMap1.h"

class CPlayScene : public CScene
{
protected:
	LPGAMEOBJECT player;					// A play scene has to have player, right? 
	vector<LPGAMEOBJECT> objects_Enemy;
	vector<LPGAMEOBJECT> objects_Map;
	vector<LPGAMEOBJECT> objects;
	shared_ptr<CGameMap> mMap;
public:
	CPlayScene(string id, string filePath);
	void SwitchPlayer(LPGAMEOBJECT newPlayer);
	virtual bool Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual string GetScenceFilePath() { return sceneFilePath; }
	
	LPGAMEOBJECT GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};


class CPlayScenceKeyHandler : public CScenceKeyHandler
{
	CMario* currentPlayer;
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

