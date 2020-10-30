#include "AnimationFrame.h"

class CAnimation
{
	string id;
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(string id, int defaultTime = 100) { this->id = id; this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(string spriteId, DWORD time = 0);

	void Render(float x, float y, D3DXVECTOR2 scale, int alpha = 255);
};

typedef CAnimation* LPANIMATION;