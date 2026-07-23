#include "SceneMain.h"
#include "Player.h"
#include "Enemy.h"

SceneMain::SceneMain()
{
	m_pPlayer = new Player;
	m_pEnemy = new Enemy;
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
}

void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
}

void SceneMain::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
}
