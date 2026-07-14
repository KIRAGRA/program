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

	int GetMousePosX()const { return m_mousePosX;}
	int GetMousePosY()const { return m_mousePosY;}

	

private:


	int m_mousePosX = WIDTH / 2;
	int m_mousePosY = HEIGHT / 2;
	

	int m_playerType;

};

