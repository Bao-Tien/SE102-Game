#include "Scence.h"

CScene::CScene(std::string id, std::string filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;

}

void CScene::CleanupListObjects(vector<LPGAMEOBJECT>& listObjs) {
	for (int i = 0; i < listObjs.size(); i++)
		delete listObjs[i];
	listObjs.clear();
}