#include <DxLib.h>
#include "Enemy.h"


Enemy::Enemy()
{
	m_handle = LoadGraph("data/enemy.png");
}

Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawGraph(150, 0, m_handle, true);
}
