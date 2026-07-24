#include "Character.h"
#include <DxLib.h>
namespace
{
	constexpr float kGravity = 1.5f;//重力
}

Character::Character() :
	m_handle(-1),
	m_isRight(true)
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
	Gravity();
}

void Character::Draw()
{
	DrawGraphF(0, 0, m_handle, true);
}

void Character::Gravity()
{
	m_move.y += kGravity;
}
