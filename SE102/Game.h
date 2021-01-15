#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Scence.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	

	int screen_width;
	int screen_height;

	string current_scene;

public:
	CCamera* camera;
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DXVECTOR2 scale = Vector2(1,1), int alpha = 255, Vector2 pivot = Vector2(0,0));
	
	void DrawWithoutConverting(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DXVECTOR2 scale = Vector2(1, 1), int alpha = 255, Vector2 pivot = Vector2(0, 0));
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	bool Load(string gameFile);
	string GetCurrentSceneId() { return current_scene; }
	void SwitchScene(string scene_id);

	int GetScreenWidth() { 
		return screen_width; 
	}
	int GetScreenHeight() { return screen_height; }

	Vector2 GetPosCamera() { return camera->GetCamPosition(); }
	
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny); //CGameObject cung cos SweptAABB -> vay khac gi nhau

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y);

	static CGame* GetInstance();

	~CGame();
};


