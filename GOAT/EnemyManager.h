#pragma once
#include "Enemy2.h"

class EnemyManager
{
public:
	EnemyManager();
	virtual~EnemyManager();


	void Init();
	void Update();
	void Draw();

	float GetRandPos(int _min, int _max);

private:

	

	int m_count;

	Enemy2 m_enemy[3];//

};

