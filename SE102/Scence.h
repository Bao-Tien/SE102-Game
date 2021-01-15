#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include <string>
#include "GameObject.h"
#include "GameMap1.h"


class CScene
{
protected:
	CKeyEventHandler* key_handler; 
	std::string id;
	std::string sceneFilePath;   
	shared_ptr<CGameMap> mMap;
	vector<LPGAMEOBJECT> objects_Map;
	long long sceneTime = 0;
	long long scenePoint = 0;
	LPGAMEOBJECT player;

public:
	CScene(std::string, std::string); 
	
	void CleanupListObjects(vector<LPGAMEOBJECT>&);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual bool Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD) = 0;
	virtual void Render() = 0;
	virtual void SwitchPlayer(LPGAMEOBJECT) = 0;
	virtual void AddPoint(long long point) { scenePoint += point; }
	virtual LPGAMEOBJECT GetPlayer() { return player; }
	
	virtual std::string GetScenceFilePath() { return sceneFilePath; }
};
typedef CScene* LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene* s) :CKeyEventHandler() { scence = s; }
};