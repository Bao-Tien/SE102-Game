#include "Camera.h"
#include "Game.h"
#include "ScenceManager.h"

CCamera::CCamera() {
	this->camPosition = Vector2(0, 0);
	this->camSize = Vector2(CGame::GetInstance()->GetScreenWidth(), CGame::GetInstance()->GetScreenHeight());
	this->positionController = NULL;
}

CCamera::~CCamera() {

}

void CCamera::InitPositionController(CGameObject* player) {
	
	this->positionController = player;
}

Vector2 CCamera::GetCamPosition() {
	return camPosition;
}

void CCamera::SetCamPosition(Vector2 pos) {
	if (pos.x < 0) pos.x = 0; // overflow left side
	if (pos.x + camSize.x > 8448) pos.x = 8448 - camSize.x;

	if (pos.y < 0) pos.y = 0;
	
	camPosition = pos;
}

Vector2 CCamera::ConvertPosition(Vector2 pos) {
	//chuyen tu the gioi that sang camera
	return Vector2(pos.x - camPosition.x, pos.y - camPosition.y);
}

void CCamera::UpdateCamPosition() {
	float left, top, right, bottom;
	positionController->GetBoundingBox(left, top, right, bottom); 
	SetCamPosition(Vector2((int)(positionController->x+20 - camSize.x / 2), 550));
	
}

void CCamera::Update(DWORD dt) {
	
	UpdateCamPosition();
	
}

void CCamera::Render() {
	
}