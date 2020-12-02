#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"

class CPlayScene : public CScene
{
protected:
	vector<LPGAMEOBJECT> objects_Enemy;
	vector<LPGAMEOBJECT> objects_Active;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_Priority;
	
public:
	CPlayScene(string id, string filePath);
	void SwitchPlayer(LPGAMEOBJECT newPlayer);
	virtual bool Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void AddObjToObjects_Active(LPGAMEOBJECT a);
	virtual vector<LPGAMEOBJECT> GetObjEnemy() { return objects_Enemy; }
	virtual vector<LPGAMEOBJECT> GetObjMap() { return objects_Map; }
	LPGAMEOBJECT GetPlayer() { return player; }
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

