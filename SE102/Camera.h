#pragma once
#include "Transform.h"
#include "GameObject.h"
#include "GameMap1.h"
class CCamera {

protected:

	Vector2 camPosition = Vector2(0.0f, 0.0f);
	Vector2 camSize; //px
	Vector2 mapSize;
	CGameObject* positionController; 
	
public:

	CCamera();
	~CCamera();
	Vector2 GetCamPosition();
	Vector2 GetCamSize() { return camSize; }
	void SetCamPosition(Vector2 pos);
	Vector2 ConvertPosition(Vector2 pos);

	void InitPositionController(CGameObject* a);

	void UpdateCamPosition();

	void Update(DWORD dt);
	void Render();
};