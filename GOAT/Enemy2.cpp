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

	constexpr int kSpawnFrame = 250.0f;

	constexpr int kHalfSize = 50;

	constexpr int kChipWidth = 16;
	constexpr int kChipHeight = 16;

	
	

}

Enemy2::Enemy2():
	m_halfSize(0),
	m_isHit(0),
	m_firstPos({ 0,0 })
	

{
	
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init(Vec2 _pos)
{
	m_isHit = false;
	m_halfSize = kHalfSize;
	m_pos = _pos;
	m_firstPos = _pos;
}

void Enemy2::Update()
{
	
}

void Enemy2::Draw()
{
	if (m_isHit)
	{
		DrawCircle(m_pos.x, m_pos.y, m_halfSize, GetColor(255, 0, 0), true);
		//DrawBox(m_pos.x, m_pos.y, 10, 10, GetColor(255, 255, 255), true);
		m_isHit = false;
	}
	else
	{
		DrawCircle(m_pos.x, m_pos.y,  m_halfSize, GetColor(255, 255, 255), true);
		//DrawBox(m_pos.x, m_pos.y, 10, 10, GetColor(255, 255, 255), true);
	}


}

void Enemy2::CheckHit()
{

}
