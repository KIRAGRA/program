#include "SceneMain.h"
#include "Input.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Vec2.h"
#include <DxLib.h>
SceneMain::SceneMain():
	m_pInput(nullptr),
	m_pEnemy(nullptr),
	m_pEnemy2(nullptr)
{
}

SceneMain::~SceneMain()
{
	delete m_pInput;
	delete m_pEnemy;
	delete m_pEnemy2;
}

void SceneMain::Init()
{
	m_pInput = new Input;
	
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
		m_pEnemy2[i]->Init({ 200 + idx *100, 200 });

	}
	m_pInput->Init();
	
	

}

void SceneMain::Update()
{
	//左クリックしているかを判定
	bool IsLeftClick = m_pInput->IsTrigger(MOUSE_INPUT_LEFT);

	//左クリックしたときにあたっているかを判定する



	m_pInput->Update();
	for (int i = 0; i < 1;i++)
	{
		if (IsLeftClick)
		{
			bool isHit = ColCheck(m_pEnemy[i]->GetPos(), m_pEnemy[i]->GetHalfSize());
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
		}
		m_pEnemy2[i]->Update();
	}
}

void SceneMain::Draw()
{
	m_pInput->Draw();
	for (int i = 0; i < 1;i++)
	{
		m_pEnemy[i]->Draw();
	}
	//雑魚敵
	for (int i = 0; i < 1;i++)
	{
		m_pEnemy2[i]->Draw();
	}
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
