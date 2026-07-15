#include "Computer.h"
#include "Mouse.h"
#include "Car.h"
#include <stdlib.h>
#include <DxLib.h>
#include "MainScene.h"
#include "GameDefine.h"
using namespace GameDefine;

Computer::Computer() :
	m_computerType(0)
{
}

Computer::~Computer()
{
}

void Computer::Init()
{
	for (int i = 0; i < CAR_MAX; i++)
	{
		m_computerX[i] = rand() % 180 + 270;
		m_computerY[i] = -100;
		m_computerType[i] = Car::CarType::YELLOW + rand() % 3;
	}
}

void Computer::End()
{
}

void Computer::Update()
{

	for (int i = 0; i <= COM_MAX; i++)
	{
		m_computerY[i] += (i + 1);

		//画面の下から外に出たかを判定
		if (m_computerY[i] > HEIGHT + 100)
		{
			m_computerX[i] = rand() % 180 + 270;
			m_computerY[i] = -100;
			m_computerType[i] = Car::CarType::YELLOW + rand() % 3;
		}
	}
}

void Computer::Draw()
{
}
