#pragma once
#include "GameDefine.h"
using namespace GameDefine;

class Mouse;
class Computer;

class Car
{
public:
	Car();
	~Car();

	void Init();
	void End();
	void Update();
	void Draw();

public:
	enum CarType
	{
		RED,
		YELLOW,
		BLUE,
		TRUCK
	};

	
	
	void DrawCar(int x, int y, int type);
		


private:
	//車のハンドルの配列
	int  m_carsH[CAR_MAX];

	Mouse* m_pgetMouse;

	Computer* m_pgetComputer;


	
};

