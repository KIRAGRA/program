#pragma once
#include <cmath>
class Vec2
{
public:
	Vec2();
	virtual~Vec2();

	void Init();
	void End();
	void Update();

	

public:

	float x = 0;
	float y = 0;

	Vec2(float posX, float posY):
		x(posX),
		y(posY)
	{
	}

	//ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì2æ‚ğ•Ô‚·
	float sqrLength();
		


};

