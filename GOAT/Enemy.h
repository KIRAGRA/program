#pragma once
#include "Vec2.h"
class Enemy
{
public:
	Enemy();
	virtual~Enemy();



	void Init(Vec2 _pos);
	void Update();
	void Draw();
	
	void CheckHit();
	void SetIsHit(bool _isHit) { m_isHit = _isHit; };
	Vec2 GetPos() const { return m_pos; };
	float GetHalfSize() const { return m_halfSize; };

protected:
	Vec2 m_pos;


private:
	//移動処理
	void Move();

	int m_enemyHp;

	//

	Vec2 m_firstPos;

	//出現時間
	int m_time;
	
	//enemyサイズ
	int m_halfSize;
	//
	bool m_isHit;


	 


};

