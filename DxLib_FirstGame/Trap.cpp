#include "Trap.h"
#include <cmath>
#include "DxLib.h"
#include "Game.h"
namespace
{
	//移動開始までの待ち時間(フレーム数)
	constexpr int kStartWaitFrame = 180;



	//回転速度
	constexpr double kRotaSpeed = -0.2;

	//のこぎりの移動速度
	constexpr float kSpeed = 2.0f;

	//のこぎり当たり半径
	constexpr float kColRadius = 20.0f;
}


Trap::Trap():
m_graphHandle(-1),
m_waitFrame(0),
m_x(0.0f),
m_y(0.0f),
m_vecX(0.0f),
m_vecY(0.0f),

m_angle(0.0)


{
}

Trap::~Trap()
{
}

void Trap::Init()
{
	//開始待ち
	m_waitFrame = kStartWaitFrame;

	m_x = kStartWaitFrame;
	m_y = kStartWaitFrame;

	//進行方向を決定

	//ランダムな角度を生成する
	float angle = (DX_TWO_PI_F / 65536) * GetRand(65536 - 1);
	//生成した角度にkSpeedで移動するベクトル
	m_vecX = cosf(angle) * kSpeed;
	m_vecY = sinf(angle) * kSpeed;

	m_angle = 0.0;
}

void Trap::End()
{
}

void Trap::Update()
{
	//開始待ち状態でも行う処理
	m_angle += kRotaSpeed;

	//待ち時間カウントダウン
	m_waitFrame--;
	if (m_waitFrame > 0) return;

	//以降は待ち時間の間は処理しない

	m_x += m_vecX;
	m_y += m_vecY;

	//画面端で反射

	if (m_x < 0.0f)
	{
		m_x = 0.0f;
		//反射
		m_vecX *= -1;
	}
	if (m_x > Game::kScreenWidth)
	{
		m_x = Game::kScreenWidth;
		//反射
		m_vecX *= -1;
	}

	if (m_y < 0.0f)
	{
		m_y = 0.0f;
		//反射
		m_vecY *= -1;
	}
	if (m_y > Game::kScreenHeight)
	{
		m_y = Game::kScreenHeight;
		//反射
		m_vecY *= -1;
	}



}

void Trap::Draw()
{
	//DrawGraph(m_x, m_y, m_graphHandle, true);

	DrawRotaGraph(m_x, m_y,		//中心座標
		1.0, m_angle,
		m_graphHandle, true);
}

float Trap::GetColCenterX() const
{
	return m_x;
}

float Trap::GetColCenterY() const
{
	return m_y;
}

float Trap::GetRadius() const
{
	return kColRadius;
}
