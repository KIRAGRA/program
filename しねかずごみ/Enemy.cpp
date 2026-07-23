#include "Enemy.h"
#include <DxLib.h>
Enemy::Enemy()
{
	m_handle = LoadGraph("data/enemy.png");
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
	Character::Draw();
}
