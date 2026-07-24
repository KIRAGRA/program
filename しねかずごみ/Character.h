#pragma once
#include "Vec2.h"

class Character
{
public:
	Character();
	virtual~Character();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

protected:
	void Gravity();

public:
	int m_handle;

protected:
	Vec2 m_pos;//座標
	Vec2 m_move;//移動量

public:
	bool m_isRight;//キャラクターが右を向いているか




};

