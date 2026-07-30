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

	constexpr int kSpeed = 7;

	constexpr int kSpawnFrame = 250.0f;

	constexpr int kHalfSize = 50;

	constexpr int kEnemyHp = 1;
}
Enemy::Enemy() :
	m_time(0),
	m_halfSize(0),
	m_isHit(0),
	m_firstPos({0,0}),
	m_enemyHp(0)

{
}

Enemy::~Enemy()
{
}

void Enemy::Init(Vec2 _pos)
{

	m_enemyHp = kEnemyHp;
	m_isHit = false;
	m_halfSize = kHalfSize;
	m_pos = _pos;
	m_firstPos = _pos;
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
	if (m_isHit == true)
	{
		// 当たっているときの処理
		DrawCircle(m_pos.x, m_pos.y, m_halfSize, GetColor(255, 0, 0), true);
		printfDx("HIT\n");
		m_isHit = false;
	}
	else if(m_isHit == false)
	{
		// 当たっていないときの処理
		DrawCircle(m_pos.x, m_pos.y, m_halfSize, GetColor(255, 255, 255), true);
	}


}

void Enemy::Move()
{
	m_pos.x += kSpeed;
	
}



void Enemy::CheckHit()
{
	/*//現在のマウスの位置を取得
	int _mousePosX;
	int _mousePosY;
	GetMousePoint(&_mousePosX, &_mousePosY);
	Vec2 mousePos;
	mousePos.x = _mousePosX;
	mousePos.y = _mousePosY;

	//マウスが当たっているか
	//マウスの位置からとエネミーの位置のベクトルを作成
	Vec2 mouseToEnemy;
	mouseToEnemy.x = m_pos.x - mousePos.x;
	mouseToEnemy.y = m_pos.y  - mousePos.y;

	//マウスからenemyへの距離
	int mouseToEnemyLen = mouseToEnemy.sqrLength();

	//マウスからenemyへの距離がenemyの半径より小さかったら当たっている
	if (mouseToEnemyLen < (m_halfSize*m_halfSize))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}*/
}
