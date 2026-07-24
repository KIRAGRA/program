#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Character.h"
namespace
{
	constexpr float kSpeed = 20.0f;//移動速度
}
Player::Player()
{ 
	
	m_handle = LoadGraph("data/player.png");
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{

	Move();
	m_pos += m_move;
	Character::Update();
}

void Player::Draw()
{
	if (m_isRight)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
}


void Player::Move()
{
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_move.x = -kSpeed;
		m_isRight = false;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_move.x = kSpeed;
		m_isRight = true;
	}
	else
	{
		m_move.x = 0.0f;
	}
}

