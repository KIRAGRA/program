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
	m_firstPos({ 0,0 }),
	m_enemyHandle(-1)
{
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init(Vec2 _pos)
{

	m_enemyHandle = LoadGraph("data/car.png");

	m_isHit = false;
	m_halfSize = kHalfSize;
	m_pos = _pos;
	m_firstPos = _pos;
	m_time = 0;
}

void Enemy2::Update()
{
	m_time++;

	if (120 < m_time)
	{
		m_time = 0;
	}

}

void Enemy2::Draw()
{
	if (m_isHit)
	{
		
		m_isHit = false;
	}
	else
	{

		for (int i = 0;i < kEnemyMax; i++)
		{
			if (i < m_time)
			{
				DrawGraphCenter(m_pos, m_enemyHandle);
			}

		}
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
