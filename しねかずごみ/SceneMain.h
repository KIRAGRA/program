#pragma once
class Player;
class Enemy;
class Shot;
class SceneMain
{
public:
	SceneMain();
	virtual~SceneMain();

	void Init();
	void Update();
	void Draw();

private:
	void UpdateShot();


	void DeleteShot(int index);


private:
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Shot* m_pShot[3];
};

//Draw
//if (!m_pShot)return;
//m_pShot->Draw();

//
//m_pShot = newShot;//弾の保持
//	}
//
//if (!m_pShot)return;
//m_pShot->Update();
////画面外に出たら削除する
//bool isDelete = false;
//isDelete = m_pShot->GetPos().x < 0 || m_pShot->GetPos().x > kScreenWidth;
//if (!isDelete)return;
//DeleteShot();