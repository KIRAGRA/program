#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Character.h"
#include "Shot.h"
namespace
{
	constexpr float kSpeed = 20.0f;//移動速度
	constexpr float kJumpPower = 20.0f;//ジャンプ力


	constexpr int kSmallJumpFrame = 8;//小ジャンプのフレーム数
	constexpr int kMediumJunpFrame = 13;//中ジャンプのフレーム数
	constexpr float kSmallJumpHeight = 0.5f;//小ジャンプの高さ
	constexpr float kMediumJumpHeight = 1.0f;//中ジャンプの高さ
	constexpr float kBigJumpHeight = 1.5f;//大ジャンプの高さ

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
	Jump();
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

Shot* Player::CreateShot()
{
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		Shot* pShot = new Shot();
		pShot->SetInfo(m_pos, m_isRight);

		return pShot;
	}
	return nullptr;
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

void Player::Jump()
{
	//ジャンプ中は飛ばす
	if (!m_isGround)return;
	//ボタンを押したらフレーム数を計算し始める
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isJumpPreparing = true;
	}
	if (!m_isJumpPreparing)return;
	m_jumpFrame++;

	float jumpHeight = kJumpPower;//ジャンプの高さを決める

	//ボタンを離した瞬間にジャンプする
	if (!Pad::IsRelease(PAD_INPUT_1))return;

	//小ジャンプ
	if (m_jumpFrame < kSmallJumpFrame)
	{
		jumpHeight = kSmallJumpHeight;
	}
	//中ジャンプ
	else if (m_jumpFrame < kMediumJunpFrame)
	{
		jumpHeight = kMediumJumpHeight;
	}
	//大ジャンプ
	else
	{
		jumpHeight = kBigJumpHeight;
	}

	m_move.y = -kJumpPower * jumpHeight;
	m_isGround = false;
	m_isJumpPreparing = false;

}

