#include "Bg.h"
#include <DxLib.h>
#include "GameDefine.h"
using namespace GameDefine;

Bg::Bg():
	m_bgH(-1),//Handleは全部-1で初期化
	m_bgY(0)
{
}

Bg::~Bg()
{
	DeleteGraph(m_bgH);
}

void Bg::Init()
{
	m_bgH  = LoadGraph("image/bg.png");
	
}

void Bg::Update()
{
	m_bgY = m_bgY + 10;
	if (m_bgY >= HEIGHT) { m_bgY -= HEIGHT;}

}

void Bg::Draw()
{
	DrawGraph(0, m_bgY - HEIGHT,m_bgH,false);
	DrawGraph(0,m_bgY,m_bgH,false);

}

