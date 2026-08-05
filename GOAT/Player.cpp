#include "Player.h"
#include <DxLib.h>

Player::Player():
	m_bulletAttack(0),
	m_playerHandle(-1),
	m_animFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_playerHandle = LoadGraph("Gun/ShootGun_result.png");
}

void Player::Update()
{
	//m_animFrame + 12;

	//if (m_animFrame < 144)
	//{
	//	m_animFrame = 12;
	//}
}

void Player::Draw()
{
	DrawRectGraph(20, 500, 
		0,0,4880 / 12,305,
		m_playerHandle, false);

	//DrawGraph(-100, 500, m_playerHandle, true);
}
