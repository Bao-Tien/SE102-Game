#pragma once
#include "Scence.h"
#include "MarioSelectScence.h"

class CSelectionScence :public CScene
{
	vector<LPGAMEOBJECT> objects_NoActive;
	vector<LPGAMEOBJECT> objects_Active;
public:
	CSelectionScence(std::string id, std::string filePath);

	bool Load() override;
	void Unload() override;
	void Update(DWORD dt) override;
	void Render() override;
	void SwitchPlayer(LPGAMEOBJECT newPlayer) override {};
	LPGAMEOBJECT GetPlayer() { return player; }

};

class CSelectionScenceKeyHandler : public CScenceKeyHandler
{
	CMarioSelectScence* currentPlayer;
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CSelectionScenceKeyHandler(CScene* s) : CScenceKeyHandler(s) {};
};



