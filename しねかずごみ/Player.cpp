#include "Player.h"
#include <DxLib.h>
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
}

void Player::Draw()
{
	Character::Draw();
}

