#include "Enemy.h"
#include <DxLib.h>
#include "Vec2.h"
#include "Input.h"
#include "GameDefine.h"
using namespace Game;

namespace
{
	constexpr int kFirstPosX = -100;
	constexpr int kFirstPosY = 100;

	constexpr int kSpeed = 25;

	constexpr int kSpawnFrame = 250.0f;

	constexpr int kHalfSize = 50;

	constexpr int kEnemyHp = 1;


	constexpr float kWidth = 200;
	constexpr float kHeight = 200;


}
Enemy::Enemy() :
	m_time(0),
	m_halfSize(0),
	m_isHit(0),
	m_firstPos({0,0}),
	m_enemyHp(0),
	m_enemyHandle(-1),
	m_Bg(-1),
	m_width(0.0f),
	m_height(0.0f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(Vec2 _pos)
{

	m_enemyHandle = LoadGraph("data/car.png");

	m_Bg = LoadGraph("jail.jpg");

	m_enemyHp = kEnemyHp;
	m_isHit = false;
	m_halfSize = kHalfSize;
	m_pos = _pos;
	m_firstPos = _pos;

	m_width = kWidth;
	m_height = kHeight;



}

void Enemy::Update()
{
	//時間で再出現
	if (m_time > kSpawnFrame)
	{
		//位置の初期化
		m_pos = m_firstPos;

		//タイマーのリセット
		m_time = 0;
	}
	//タイマーの更新
	m_time++;

	if (m_enemyHp < 0)
	{
		//DeleteObject();
	}

	
	//移動処理
	Move();
	
}

void Enemy::Draw()
{
	DrawGraph(0, 0, m_Bg, true);
	if (m_isHit == true)
	{
		printfDx("HIT\n");
		m_isHit = false;
	}
	else if(m_isHit == false)
	{
		// 当たっていないときの処理
		
		DrawGraphCenter(m_pos, m_enemyHandle);
		
	}
	


}

void Enemy::Move()
{
	m_pos.x += kSpeed;
	
}

void Enemy::DrawBoxCenter(Vec2 _enePos, float _width, float _height, unsigned int Color)
{
	float Left = _enePos.x - (_width / 2);
	float Right = _enePos.x + (_width / 2);
	float Bottom = _enePos.y + (_height / 2);
	float Top = _enePos.y - (_height / 2);

	DrawBox(Left, Top, Right, Bottom, Color, true);


}

void Enemy::DrawGraphCenter(Vec2 _enePos, int _graphHandle)
{
	int width, height;

	GetGraphSize(_graphHandle, &width, &height);

	DrawTurnGraph(_enePos.x - (width * 0.5f), _enePos.y - (height * 0.5f), _graphHandle, true);

}


