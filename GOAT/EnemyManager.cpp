#include "EnemyManager.h"
#include "Vec2.h"
#include <DxLib.h>

EnemyManager::EnemyManager():
	m_count(0)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (int i = 0;i < 3; i++)
	{
		m_enemy[i].Init({ GetRandPos(100,400),GetRandPos(100,400)});
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < 3; i++)
	{
		m_enemy[i].Update();
	}

	m_count++;
	if (m_count % 10)
	{

	}

}

void EnemyManager::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		m_enemy[i].Draw();
	}
}

float EnemyManager::GetRandPos(int _min, int _max)
{
	float rand = static_cast<float>(GetRand(_max - _min) + _min);
	
	return rand;
}
