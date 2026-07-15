#pragma once
#include "GameDefine.h"
using namespace GameDefine;

class Car;

class Computer
{
public:
	Computer();
	virtual~Computer();

	void Init();
	void End();
	void Update();
	void Draw();



	int GetComputerPosX(int i)const { return m_computerX[i]; }
	int GetComputerPosY(int i)const { return m_computerY[i]; }
	int GetComputerColor(int i)const { return m_computerType[i]; }

	int x;
	int y;

	int GetComputerBoxCenterX() { return x - m_computerX[COM_MAX] / 2; }
	int GetComputerBoxCenterY() { return y - m_computerY[COM_MAX] / 2; }

	int GetWidthComputer() { return (int)( x - ((CAR_W_SIZE[m_computerType[COM_MAX]]) * (0.5))); }
	int GetHeightComputer() { return (int)( y - ((CAR_H_SIZE[m_computerType[COM_MAX]]) * (0.5))); }

private:

	int m_computerX[COM_MAX];


	int m_computerY[COM_MAX];


	int m_computerType[];



};

