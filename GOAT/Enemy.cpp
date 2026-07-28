#include "Enemy.h"
#include <DxLib.h>
namespace
{
	constexpr int kEnemySpone = 5;

	constexpr int kEnemyHp = 50;

}
Enemy::Enemy():
	m_enemyPosX(0),
	m_enemyPosY(0),
	m_enemyHandle(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}
