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

public:
	void Gravity();

public:
	int m_handle;

protected:
	Vec2 m_pos;//座標
	Vec2 m_move;//移動量


protected:
	bool m_isGround;//地面に着地しているか

protected:
	int m_jumpFrame;//ジャンプのフレーム
	bool m_isJumpPreparing;//ジャンプ準備中か



public:
	bool m_isRight;//キャラクターが右を向いているか




};

