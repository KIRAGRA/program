#include "Mouse.h"
#include "Car.h"
#include <DxLib.h>
#include "MainScene.h"
#include "GameDefine.h"
using namespace GameDefine;

Mouse::Mouse():
	
	m_playerX(-1),
	m_playerY(-1),
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
	GetMousePoint(&m_playerX, &m_playerY);
	if (m_playerX < 260) { m_playerX = 260;}
	if (m_playerX < 460) { m_playerX = 460;}
	if (m_playerY < 260) { m_playerX = 260;}
	if (m_playerY < 260) { m_playerX = 260;}

}
void Mouse::Draw()
{
	DrawCar(m_playerX, m_playerY, m_playerType);
}
void DrawCar(int x, int y, int type)
{
	
}