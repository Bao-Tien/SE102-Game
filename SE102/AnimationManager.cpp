#include "AnimationManager.h"

#include "Utils.h"
CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(string id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(string id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d\n", id);
	return ani;
}

void CAnimations::Initialization(string path)
{
	LoadAnimationFile(path);
}

bool CAnimations::LoadAnimationFile(string path)
{
	OutputDebugStringW(ToLPCWSTR(path.c_str()));
	TiXmlDocument document(path.c_str());
	if (!document.LoadFile())
	{
		OutputDebugStringW(ToLPCWSTR(document.ErrorDesc()));
		return false;
	}

	TiXmlElement* root = document.RootElement();
	TiXmlElement* info = root->FirstChildElement();

	string gameObjectID = info->Attribute("gameObjectId");
	string textureID = info->Attribute("textureId");

	for (TiXmlElement* node = info->FirstChildElement(); node != nullptr; node = node->NextSiblingElement())
	{
		string aniId = node->Attribute("aniId");
		float frameTime;
		node->QueryFloatAttribute("frameTime", &frameTime);
		CAnimation* animation = new CAnimation(aniId, frameTime);

		for (TiXmlElement* sprNode = node->FirstChildElement(); sprNode != nullptr; sprNode = sprNode->NextSiblingElement())
		{
			string id = sprNode->Attribute("id");
			float detailFrameTime = 100;
			sprNode->QueryFloatAttribute("frameTime", &detailFrameTime);
			animation->Add(id,detailFrameTime);

			OutputDebugStringW(ToLPCWSTR("|--" + id + ':' + to_string(detailFrameTime) + '\n'));
		}
		Add(aniId, animation);
	}
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}