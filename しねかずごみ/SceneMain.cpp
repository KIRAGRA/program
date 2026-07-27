#include "SceneMain.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "Vec2.h"
namespace
{
	constexpr float kScreenWidth = 1980.0f;//画面幅
	constexpr int kShotMax = 3;//一度に撃てる最大弾数
}
SceneMain::SceneMain():
	m_pShot(nullptr)
{
	for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i] = nullptr;
	}
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
	UpdateShot();
	m_pPlayer->Update();
	m_pEnemy->Update();
}

void SceneMain::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}
}

void SceneMain::UpdateShot()
{
	Shot* newShot = m_pPlayer->CreateShot();
	if (newShot != nullptr)
	{
		for (int i = 0;i < kShotMax; i++)
		{
			if (m_pShot[i] == nullptr)
			{
				m_pShot[i] = newShot;
				break;
			}
		}
	}
	for (int i = 0;i < kShotMax; i++)
	{
		if (!m_pShot[i])continue;

		m_pShot[i]->Update();


		//画面外に出たら削除する
		bool isDelete = false;
		isDelete = m_pShot[i]->GetPos().x < 0 || m_pShot[i]->GetPos().x > kScreenWidth;
		if (isDelete)
		{
			DeleteShot(i);
		}
	}
}
void SceneMain::DeleteShot(int index)
{
	if (!m_pShot[index])return;

	delete m_pShot[index];
	m_pShot[index] = nullptr;
}
