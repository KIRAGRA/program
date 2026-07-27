#include "Character.h"
#include <DxLib.h>
namespace
{
	constexpr float kGravity = 1.5f;//重力
	constexpr float kGround = 900.0f;//地面位置

}

Character::Character() :
	m_handle(-1),
	m_isRight(true),
	m_isGround(true),
	m_jumpFrame(0),
	m_isJumpPreparing(false)
{
}

Character::~Character()
{
}

void Character::Init()
{
}

void Character::Update()
{

	m_pos += m_move;
	Gravity();
	//着地処理
	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
		m_move.y = 0.0f;
		m_isGround = true;

		//ジャンプ中は飛ばす
		if (m_isJumpPreparing)return;
		m_jumpFrame = 0;
	}
}

void Character::Draw()
{
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

void Character::Gravity()
{
	m_move.y += kGravity;
}
