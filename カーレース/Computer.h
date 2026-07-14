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

private:

	int m_computerX[COM_MAX];


	int m_computerY[COM_MAX];


	int m_computerType[COM_MAX];



};

