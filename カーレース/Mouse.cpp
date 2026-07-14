#include "Mouse.h"
#include "Car.h"
#include <DxLib.h>
#include "MainScene.h"
#include "GameDefine.h"
using namespace GameDefine;

Mouse::Mouse():
	m_playerType(0)
{
}

Mouse::~Mouse()
{
}

void Mouse::Init()
{
	int m_playerType = Car::CarType::RED;
	
}

void Mouse::End()
{
}
void Mouse::Update()
{
	GetMousePoint(&m_mousePosX, &m_mousePosY);
	if (m_mousePosX < 260) { m_mousePosX = 260;}
	if (m_mousePosX > 460) { m_mousePosX = 460;}
	if (m_mousePosY < 40) { m_mousePosY = 40;}
	if (m_mousePosY > 600) { m_mousePosY = 600;}

}
void Mouse::Draw()
{
	
}
