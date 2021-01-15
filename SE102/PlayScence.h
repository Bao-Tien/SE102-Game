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
	vector<LPGAMEOBJECT> objects_Brick;
	vector<LPGAMEOBJECT> objects_Enemy;
	vector<LPGAMEOBJECT> objects_Active;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_Magic;
	vector<LPGAMEOBJECT> onlyRender;
	int synergies;
	
	
public:
	CPlayScene(string id, string filePath);
	void SwitchPlayer(LPGAMEOBJECT newPlayer);
	virtual bool Load();
	virtual void Update(DWORD dt);
	virtual void DrawChangeStringToSprite(string input, Vector2 position);
	void DrawFixedLengthNumber(string inp, Vector2 position, char defaultChar, int numLength);
	void DrawFollow(string inp1, int x1, string inp2,int x2, Vector2 position);
	virtual void Render();
	virtual void Render_HUD();
	virtual void Unload();
	virtual void AddObjToObjects_Magic(LPGAMEOBJECT a);
	virtual void AddObjToObjects_Enemy(LPGAMEOBJECT a);
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

