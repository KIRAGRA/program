#pragma once
class Enemy
{
public:
	Enemy();
	virtual~Enemy();



	void Init();
	void Update();
	void Draw();

private:
	int m_enemyPosX;
	int m_enemyPosY;

	int m_enemyHandle;
};

