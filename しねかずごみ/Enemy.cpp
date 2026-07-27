#include "Enemy.h"
#include <DxLib.h>
#include "Character.h"

namespace
{
	float kGravity = 0.5f;
}

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
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	//Character::Draw();

	//DrawFormatString(0, 0, 0xffffff, "%f, %f", m_pos.x, m_pos.y);
}
