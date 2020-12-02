#include "GameMap1.h"
#include "Game.h"
#include "CollisionBox.h"
#include "PlatForm.h"
#include "QuestionBrick.h"
#include "Gate.h"

#define CAMERA_MARGIN			150

CGameMap::CGameMap()
{

}

CGameMap::CGameMap(int width, int height, int tileWidth, int tileHeight)
{
	this->width = width;
	this->height = height;
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
}

Vector2 CGameMap::GetBound()
{
	return Vector2(this->width * tileWidth, this->height * tileHeight);
}

shared_ptr<CTileSet> CGameMap::GetTileSetByTileID(int id)
{

	return tilesets[1];
}

void CGameMap::AddTileSet(int firstgid, shared_ptr<CTileSet> tileSet)
{
	this->tilesets[firstgid] = tileSet;
}

void CGameMap::AddLayer(shared_ptr<CMapLayer> layer)
{
	this->layers.push_back(layer);
}

void CGameMap::Update(int dt)
{
	//camPosition = CGame::GetInstance()->camera->GetCamPosition();
}

void CGameMap::Render()
{
	int col = CGame::GetInstance()->GetPosCamera().x / tileWidth;
	int row = CGame::GetInstance()->GetPosCamera().y / tileHeight;
	
	if (col > 0) col--;
	if (row > 0) row--;
	if (col < 0) col = 0;
	if (row < 0) row = 0;

	Vector2 camSize = Vector2((CGame::GetInstance()->GetScreenWidth() + CAMERA_MARGIN)/ tileWidth, 
								(CGame::GetInstance()->GetScreenHeight() + CAMERA_MARGIN) / tileHeight);

	Vector2 deltaSize = Vector2(0, 0);

	if (camSize.x > width) {
		//deltaSize.x = ( camSize.x - width ) / 2 - 1;
		camSize.x = width;
	} 
	if (camSize.y > height) {
		//deltaSize.y = (camSize.y - height) / 2 ;
		camSize.y = height;
	} 


	

	for (int i = col; i < camSize.x + col; i++) {
		for (int j = row; j < camSize.y + row; j++) {

			int x = (i + deltaSize.x) * tileWidth;
			int y = (j + deltaSize.y) * tileHeight;

			for (shared_ptr<CMapLayer> layer : layers) {
				if (layer->Hidden) continue;
				int id = layer->GetTileID(i % width, j % height);
				this->GetTileSetByTileID(id)->Draw(id, Vector2(x, y));
			}
		}
	}
}

shared_ptr<CGameMap> CGameMap::FromTMX(string filePath, vector<LPGAMEOBJECT>* objectMap, vector<LPGAMEOBJECT>* objectActive, vector<LPGAMEOBJECT>* objectNoActive)
{
	string fullPath = filePath;
	TiXmlDocument doc(fullPath.c_str());

	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		shared_ptr<CGameMap> gameMap = shared_ptr<CGameMap>(new CGameMap());

		root->QueryIntAttribute("width", &gameMap->width);
		root->QueryIntAttribute("height", &gameMap->height);
		root->QueryIntAttribute("tilewidth", &gameMap->tileWidth);
		root->QueryIntAttribute("tileheight", &gameMap->tileHeight);

		//Load tileset
		for (TiXmlElement* node = root->FirstChildElement("tileset"); node != nullptr; node = node->NextSiblingElement("tileset")) {
			CTileSet* tileSet = new CTileSet(node, filePath);
			gameMap->tilesets[tileSet->GetFirstGID()] = shared_ptr<CTileSet>(tileSet);
		}

		//Load layer
		for (TiXmlElement* node = root->FirstChildElement("layer"); node != nullptr; node = node->NextSiblingElement("layer")) {
			shared_ptr<CMapLayer> layer = shared_ptr<CMapLayer>(new CMapLayer(node));
			gameMap->AddLayer(layer);
		}

		// Load collision group objects
		for (TiXmlElement* objGroupNode = root->FirstChildElement("objectgroup"); objGroupNode != nullptr; objGroupNode = objGroupNode->NextSiblingElement("objectgroup")) {
			if (std::string(objGroupNode->Attribute("name")) == "RectCollision" 
				|| std::string(objGroupNode->Attribute("name")) == "CanNotGo") {
				for (TiXmlElement* objNode = objGroupNode->FirstChildElement("object"); objNode != nullptr; objNode = objNode->NextSiblingElement("object")) {
					LPGAMEOBJECT obj = new CCollisionBox(
						atoi(objNode->Attribute("x")),
						atoi(objNode->Attribute("y")),
					atoi(objNode->Attribute("width")),
						atoi(objNode->Attribute("height"))
					);
					objectMap->push_back(obj);
				}
			}

			if (std::string(objGroupNode->Attribute("name")) == "RectPlatform") {
				for (TiXmlElement* objNode = objGroupNode->FirstChildElement("object"); objNode != nullptr; objNode = objNode->NextSiblingElement("object")) {
					LPGAMEOBJECT obj = new CPlatForm(
						atoi(objNode->Attribute("x")),
						atoi(objNode->Attribute("y")),
						atoi(objNode->Attribute("width")),
						atoi(objNode->Attribute("height"))
					);
					objectMap->push_back(obj);
				}
			}

			if (std::string(objGroupNode->Attribute("name")) == "QuestionBrick") {
				for (TiXmlElement* objNode = objGroupNode->FirstChildElement("object"); objNode != nullptr; objNode = objNode->NextSiblingElement("object")) {
					LPGAMEOBJECT obj = new CQuestionBrick(
						atoi(objNode->Attribute("x")),
						atoi(objNode->Attribute("y")),
						atoi(objNode->Attribute("width")),
						atoi(objNode->Attribute("height"))
					);
					objectActive->push_back(obj);
				}
			}
			if (std::string(objGroupNode->Attribute("name")) == "Gate") {
				int stt=0;
				for (TiXmlElement* objNode = objGroupNode->FirstChildElement("object"); objNode != nullptr; objNode = objNode->NextSiblingElement("object")) {
					LPGAMEOBJECT obj = new CGate(
						atoi(objNode->Attribute("x")),
						atoi(objNode->Attribute("y")),
						atoi(objNode->Attribute("width")),
						atoi(objNode->Attribute("height")),
						stt++
					);
					objectNoActive->push_back(obj);
				}
			}
			
		}
		return gameMap;
	}
	throw "Load map fail!!!!!!!!";
}

void CGameMap::GetMapSize(Vector2& out) {
	out.x = this->width * tileWidth;
	out.y = this->height * tileHeight;
}

CGameMap::~CGameMap()
{
	layers.clear();
	tilesets.clear();
}
