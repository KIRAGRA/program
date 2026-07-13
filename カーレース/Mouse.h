#pragma once
#include "GameDefine.h"
using namespace GameDefine;

class Car;
class Mouse
{
public:
	Mouse();
	virtual~Mouse();

	void Init();
	void End();
	void Update();
	void Draw();

private:

	int m_playerX = WIDTH / 2;
	int m_playerY = HEIGHT / 2;

	int m_playerType;

};

