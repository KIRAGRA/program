#include <DxLib.h>
#include "Player.h"


Player::Player()
{
	m_handle = LoadGraph("data/player.png");
}

Player::~Player()
{
	DeleteGraph(m_handle);
}

void Player::Init()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawGraph(0, 0, m_handle, true);
}
