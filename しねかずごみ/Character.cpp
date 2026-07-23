#include "Character.h"
#include <DxLib.h>

Character::Character() :
	m_handle(-1)
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
}

void Character::Draw()
{
	DrawGraphF(0, 0, m_handle, true);
}
