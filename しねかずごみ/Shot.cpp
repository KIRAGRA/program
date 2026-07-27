#include <DxLib.h>
#include "Shot.h"
namespace
{
	constexpr int kSpeed = 10.0f;//弾の移動速度
}
Shot::Shot() :
	m_handle(-1),
	m_pos({0,0}),
	m_move({kSpeed,0})

{
	m_handle = LoadGraph("data/shot.png");
}

Shot::~Shot()
{
	DeleteGraph(m_handle);
}

void Shot::Init()
{
}

void Shot::Update()
{
	m_pos += m_move;
}

void Shot::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, true);
}

void Shot::SetInfo(const Vec2& pos, bool isRight)
{
	m_pos = pos;

	if (isRight)
	{
		m_move.x = kSpeed;
	}
	else
	{
		m_move.x = -kSpeed;
	}
}

