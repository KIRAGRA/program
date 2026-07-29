#pragma once
#include "Vec2.h"
class Enemy
{
public:
	Enemy();
	virtual~Enemy();



	void Init();
	void Update();
	void Draw();

	
	void CheckHit();
protected:
	Vec2 m_pos;


private:
	//移動処理
	void Move();

	void RandamSpawn();
	//


	//出現時間
	int m_time;

	int m_halfSize;

	bool m_isHit;


	 


};

