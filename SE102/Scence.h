#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include <string>

class CScene
{
protected:
	CKeyEventHandler* key_handler; 
	std::string id;
	std::string sceneFilePath;   
	
public:
	CScene(std::string id, std::string filePath); 
	
	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual bool Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual std::string GetScenceFilePath() = 0;
};
typedef CScene* LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler  // moi Scence co key event khac nhau
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene* s) :CKeyEventHandler() { scence = s; }
};