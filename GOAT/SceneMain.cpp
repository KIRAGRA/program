#include "SceneMain.h"
#include "Input.h"
#include "Enemy.h"
#include <DxLib.h>
SceneMain::SceneMain():
	m_pInput(nullptr),
	m_pEnemy(nullptr)
{
}

SceneMain::~SceneMain()
{
	delete m_pInput;
	delete m_pEnemy;
}

void SceneMain::Init()
{
	m_pInput = new Input;
	m_pEnemy = new Enemy;
	m_pInput->Init();
	m_pEnemy->Init();
}

void SceneMain::Update()
{
	//左クリックしているかを判定
	bool IsLeftClick = m_pInput->IsTrigger(MOUSE_INPUT_LEFT);

	//左クリックしたときにあたっているかを判定する
	if (IsLeftClick)
	{
		m_pEnemy->CheckHit();
	}


	m_pInput->Update();
	m_pEnemy->Update();
}

void SceneMain::Draw()
{
	m_pInput->Draw();
	m_pEnemy->Draw();
}
