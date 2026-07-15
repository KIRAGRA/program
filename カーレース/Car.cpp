#include "Car.h"
#include "MainScene.h"
#include <DxLib.h>
#include <cmath>
#include "Mouse.h"
#include "Computer.h"
#include "GameDefine.h"
using namespace GameDefine;


Car::Car() :
	m_carsH(-1),
	m_pgetMouse(nullptr),
	m_pgetComputer(nullptr)


{
}

Car::~Car()
{
	for (int i = 0; i < 4; i++)
		DeleteGraph(m_carsH[i]);
	delete m_pgetMouse;
	delete m_pgetComputer;
}

void Car::Init()
{

	m_pgetMouse = new Mouse;
	m_pgetMouse->Init();
	m_pgetComputer = new Computer;
	m_pgetComputer->Init();


	m_carsH[RED] = LoadGraph("image/car_red.png");
	m_carsH[YELLOW] = LoadGraph("image/car_yellow.png");
	m_carsH[BLUE] = LoadGraph("image/car_blue.png");
	m_carsH[TRUCK] = LoadGraph("image/truck.png");

}

void Car::End()
{
}

void Car::Update()
{
	m_pgetMouse->Update();
	m_pgetComputer->Update();

	int dx = m_pgetComputer->GetComputerBoxCenterX() - m_pgetMouse->GetMouseBoxCenterX();
	int dy = m_pgetComputer->GetComputerBoxCenterY() - m_pgetMouse->GetMouseBoxCenterY();

	int wid = (m_pgetMouse->GetWidthMouse() / 2) + (m_pgetComputer->GetWidthComputer() / 2) - 4;
	int hei = (m_pgetMouse->GetHeightMouse() / 2) + (m_pgetComputer->GetHeightComputer() / 2) - 4;

	if (dx < wid && dy < hei)
	{
		int col = GetColor(rand() % 256, rand() % 256, rand() % 256);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawBox(m_pgetMouse->GetMouseBoxCenterX() - (m_pgetMouse->GetWidthMouse() / 2),
			m_pgetMouse->GetMouseBoxCenterY() - (m_pgetComputer->GetHeightComputer() / 2),
			m_pgetMouse->GetMouseBoxCenterX() + (m_pgetMouse->GetWidthMouse() / 2),
			m_pgetMouse->GetMouseBoxCenterY() + (m_pgetComputer->GetHeightComputer() / 2),
			col, true

		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	}



}

void Car::Draw()
{
	m_pgetMouse->Draw();
	m_pgetComputer->Draw();
	DrawCar(m_pgetMouse->GetMousePosX(), m_pgetMouse->GetMousePosY(), RED);
	for (int i = 0; i <= CAR_MAX; i++)
		DrawCar(m_pgetComputer->GetComputerPosX(i), m_pgetComputer->GetComputerPosY(i), m_pgetComputer->GetComputerColor(i));




	/*DrawCar(300,360,RED);
	DrawCar(340,360,YELLOW);*/
	//DrawCar(380, 360, BLUE);
	//DrawCar(420, 360, TRUCK);




}

void Car::DrawCar(int x, int y, int type)
{
	DrawGraph(x - (CAR_W_SIZE[type] / 2), y - (CAR_H_SIZE[type] / 2), m_carsH[type], true);
}

void Car::BoxCol(int x, int y)
{




}

