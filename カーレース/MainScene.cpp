#include "MainScene.h"
#include "Bg.h"
#include "Car.h"
#include "Mouse.h"
#include <DxLib.h>
#include "GameDefine.h"
using namespace GameDefine;

MainScene::MainScene():
	m_pBg(nullptr),
	m_carsH(nullptr)
	

	
	

{
}

MainScene::~MainScene()
{
	delete m_pBg;
	delete m_carsH;
	
	
}

void MainScene::Init()
{
	m_pBg = new Bg;
	m_pBg->Init();
	m_carsH = new Car;
	m_carsH->Init();
	
	
}

void MainScene::Update()
{
	m_pBg->Update();
	m_carsH->Update();

}

void MainScene::Draw()
{
	m_pBg->Draw();
	m_carsH->Draw();
	
}

