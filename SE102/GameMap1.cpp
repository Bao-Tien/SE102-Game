#include "GameMap1.h"
#include "Game.h"
#include "CollisionBox.h"
#include "PlatForm.h"

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

	Vector2 camSize = Vector2(CGame::GetInstance()->GetScreenWidth() / tileWidth, 
								CGame::GetInstance()->GetScreenHeight() / tileHeight);

	for (int i = col; i <= camSize.x + col + 2; i++) {
		for (int j = row; j <= camSize.y + row + 2; j++) {

			int x = i * tileWidth;
			int y = j * tileHeight;

			for (shared_ptr<CMapLayer> layer : layers) {
				if (layer->Hidden) continue;
				int id = layer->GetTileID(i % width, j % height);
				this->GetTileSetByTileID(id)->Draw(id, Vector2(x, y));
			}
		}
	}
}

shared_ptr<CGameMap> CGameMap::FromTMX(string filePath, vector<LPGAMEOBJECT>* objects)
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
			if (std::string(objGroupNode->Attribute("name")) == "RectCollision") {
				for (TiXmlElement* objNode = objGroupNode->FirstChildElement("object"); objNode != nullptr; objNode = objNode->NextSiblingElement("object")) {
					LPGAMEOBJECT obj = new CCollisionBox(
						atoi(objNode->Attribute("x")),
						atoi(objNode->Attribute("y")),
						atoi(objNode->Attribute("width")),
						atoi(objNode->Attribute("height"))
					);
					objects->push_back(obj);
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
					objects->push_back(obj);
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
