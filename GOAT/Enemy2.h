#pragma once
#include "Vec2.h"
class Enmey;

class Enemy2
{
public:
	Enemy2();
	virtual~Enemy2();



	void Init(Vec2 _pos);
	void Update();
	void Draw();

	void CheckHit();
	void SetIsHit(bool _isHit) { m_isHit = _isHit; };
	Vec2 GetPos() const { return m_pos; };
	float GetHalfSize() const { return m_halfSize; };

	void DrawGraphCenter(Vec2 _enePos, int _graphHandle);

protected:
	Vec2 m_pos;

	

	private:

	Vec2 m_firstPos;
		
	//enemyサイズ
	int m_halfSize;

	int m_score;

	bool m_isHit;

	int m_enemyHandle;

	int m_time;

	bool isArrived;
};

