#include "Enemy2.h"
#include "Enemy.h"
#include <DxLib.h>
#include "Vec2.h"
#include "Input.h"
#include "GameDefine.h"
using namespace Game;

namespace
{
	constexpr int kFirstPosX = 100;
	constexpr int kFirstPosY = 300;

	constexpr int kSpeed = 7;

	constexpr int kSpawnFrame = 100.0f;

	constexpr int kEnemyMax = 5.0f;

	constexpr int kHalfSize = 50;

	constexpr int kChipWidth = 16;
	constexpr int kChipHeight = 16;


}

Enemy2::Enemy2():
	m_halfSize(0),
	m_isHit(0),
	m_time(0),
	m_EnemyHp(0),
	m_firstPos({ 0,0 }),
	m_enemyHandle(-1)
{
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init()
{

	m_enemyHandle = LoadGraph("data/car.png");

	m_isHit = false;
	m_halfSize = kHalfSize;

	Vec2 pos = { static_cast<float>(GetRand(WIDTH)), static_cast<float>(GetRand(HEIGHT)) };
	m_pos = pos;
	m_firstPos = pos;
	m_time = 0;
	m_EnemyHp = 3;
}

void Enemy2::Update()
{
	m_time++;

	if (120 < m_time)
	{
		m_time = 0;
	}
	if (m_isHit)
	{
		m_pos.x = static_cast<float>(GetRand(WIDTH));
		m_pos.y = static_cast<float>(GetRand(HEIGHT));
		m_isHit = false;
	}

}

void Enemy2::Draw()
{
	
	if (!m_isHit)
	{
		DrawGraphCenter(m_pos, m_enemyHandle);
		DrawCircle(m_pos.x, m_pos.y, m_halfSize, GetColor(255, 0, 0), false);
	}
	
}

void Enemy2::CheckHit()
{

}

void Enemy2::DrawGraphCenter(Vec2 _enePos, int _graphHandle)
{
	int width, height;

	GetGraphSize(_graphHandle, &width, &height);

	//DrawTurnGraph(GetRand(_enePos.x - (width * 0.5f)), GetRand(_enePos.y - (height * 0.5f)), _graphHandle, true);

	DrawTurnGraph(_enePos.x - (width * 0.5f), _enePos.y - (height * 0.5f), _graphHandle, true);
	
	
}
