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

	int GetMousePosX()const { return m_mousePosX; }
	int GetMousePosY()const { return m_mousePosY; }

	int x;
	int y;

	int GetMouseBoxCenterX() { return x - (m_mousePosX / 2); }
	int GetMouseBoxCenterY() { return  y - (m_mousePosY / 2); }

	int GetWidthMouse() { return x - (CAR_W_SIZE[m_playerType] / 2); }
	int GetHeightMouse() { return y - (CAR_H_SIZE[m_playerType] / 2); }


private:


	int m_mousePosX = WIDTH / 2;
	int m_mousePosY = HEIGHT / 2;


	int m_playerType;

};

