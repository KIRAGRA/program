#include "SceneMain.h"
#include "Input.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Enemy2.h"
#include "Vec2.h"
#include "Player.h"
#include <DxLib.h>
namespace
{
	constexpr int kScoreUp = 100;
}
SceneMain::SceneMain():
	m_pInput(nullptr),
	m_pEnemy(nullptr),
	m_pEnemy2(nullptr),
	m_pPlayer(nullptr),
	m_pEnemyManager(nullptr), 
	m_score(0)
	
	
{
}

SceneMain::~SceneMain()
{
	delete m_pInput;
	delete m_pEnemy;
	delete m_pEnemy2;
	delete m_pPlayer;
	delete m_pEnemyManager;
}

void SceneMain::Init()
{
	m_pInput = new Input;
	m_pInput->Init();
	m_pPlayer = new Player;
	m_pPlayer->Init();
	m_pEnemyManager = new EnemyManager;
	m_pEnemyManager->Init();
	for (int i = 0; i < 1; i++)
	{
		float idx = static_cast<float>(i);
		m_pEnemy[i] = new Enemy;
		m_pEnemy[i]->Init({ -100 + idx *100, 200 });

	}
	//雑魚敵
	for (int i = 0; i < 1; i++)
	{
		float idx = static_cast<float>(i);
		m_pEnemy2[i] = new Enemy2;
		m_pEnemy2[i]->Init({ static_cast<float>(GetRand(200 + idx * 100)), static_cast<float>( GetRand(200 + idx * 100)) });

	}

	
	

}

void SceneMain::Update()
{
	

	//左クリックしているかを判定
	bool IsLeftClick = m_pInput->IsTrigger(MOUSE_INPUT_LEFT);

	//左クリックしたときにあたっているかを判定する


	m_pPlayer->Update();
	m_pInput->Update();
	m_pEnemyManager->Update();
	for (int i = 0; i < 1;i++)
	{
		if (IsLeftClick)
		{
			bool isHit = BoxColCheck(m_pEnemy[i]->GetPos(), m_pEnemy[i]->GetWidth(), m_pEnemy[i]->GetHeight());
			//m_pEnemy[i]->CheckHit();
			m_pEnemy[i]->SetIsHit(isHit);
			
		}
		m_pEnemy[i]->Update();
	}
	//雑魚敵
	for (int i = 0; i < 1;i++)
	{
		if (IsLeftClick)
		{
			bool isHit = ColCheck(m_pEnemy2[i]->GetPos(), m_pEnemy2[i]->GetHalfSize());
			//m_pEnemy2[i]->CheckHit();
			m_pEnemy2[i]->SetIsHit(isHit);
			if (isHit == true)
			{
				m_score += kScoreUp;
			}
		
		
		}
		m_pEnemy2[i]->Update();
	}
}

void SceneMain::Draw()
{
	m_pInput->Draw();
	m_pPlayer->Draw();
	m_pEnemyManager->Draw();
	for (int i = 0; i < 1;i++)
	{
		m_pEnemy[i]->Draw();
	}
	//雑魚敵
	for (int i = 0; i < 1;i++)
	{
		//m_pEnemy2[i]->Draw();


	}
 DrawFormatString(100, 100, GetColor(255, 255, 255), "SCORE: %d", m_score);
	


}

bool SceneMain::ColCheck(Vec2 _enePos, float _halfSize)
{
	//現在のマウスの位置を取得
	/*int _mousePosX;
	int _mousePosY;
	GetMousePoint(&_mousePosX, &_mousePosY);
	Vec2 mousePos;
	mousePos.x = _mousePosX;
	mousePos.y = _mousePosY;*/

	Vec2 mousePos = m_pInput->GetMousePos();

	//マウスが当たっているか
	//マウスの位置からとエネミーの位置のベクトルを作成
	Vec2 mouseToEnemy;
	mouseToEnemy.x = _enePos.x - mousePos.x;
	mouseToEnemy.y = _enePos.y - mousePos.y;

	//マウスからenemyへの距離
	int mouseToEnemyLen = mouseToEnemy.sqrLength();

	//マウスからenemyへの距離がenemyの半径より小さかったら当たっている
	if (mouseToEnemyLen < (_halfSize * _halfSize))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SceneMain::BoxColCheck(Vec2 _enePos, float _width,float _height)
{
	Vec2 mousePos = m_pInput->GetMousePos();

	float Left = _enePos.x - (_width / 2);
	float Right = _enePos.x + (_width / 2);
	float Bottom = _enePos.y + (_height / 2);
	float Top = _enePos.y - (_height / 2);

	if (mousePos.x < Left)
	{
		return false;
	}
	if (mousePos.x > Right)
	{
		return false;
	}
	if (mousePos.y > Bottom)
	{
		return false;
	}
	if (mousePos.y < Top)
	{
		return false;
	}
	return true;

}

