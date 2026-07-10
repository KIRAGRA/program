#include "Car.h"
#include "GameDefine.h"
#include "DxLib.h"
using namespace GameDefine;


Car::Car():
	m_carsH(-1)
	
{
}

Car::~Car()
{
	delete m_carsH;
}

void Car::Init()
{
	
	m_carsH[RED] = LoadGraph("image/car_red.png");
	m_carsH[YELLOW] = LoadGraph("image/car_yellow.png");
	m_carsH[BLUE ] = LoadGraph("image/car_blue.png");
	m_carsH[TRUCK] = LoadGraph("image/truck.png");




	
}

void Car::End()
{
}

void Car::Update()
{
}

void Car::Draw()
{
	DrawCar(300,360,RED);
	DrawCar(340,360,YELLOW);
	DrawCar(380,360,BLUE);
	DrawCar(420,360,TRUCK);
	
}

void Car::DrawCar(int x, int y, int type)
{
	DrawGraph(x - CAR_W_SIZE[type] / 2, y - CAR_H_SIZE[type] / 2, m_carsH[type], true);
}