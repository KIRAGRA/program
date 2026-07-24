#include "Enemy.h"
#include <DxLib.h>
#include "Character.h"

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

	Character::Update();
}


void Enemy::Draw()
{
	Character::Draw();
}
