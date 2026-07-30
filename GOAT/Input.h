#pragma once
#include "Vec2.h"
class Input
{
public:
	Input();
	virtual~Input();

	void Init();
	void Update();
	void Draw();

	Vec2 GetMousePos()const { return{ static_cast<float>(m_mousePosX), static_cast<float>(m_mousePosY) }; };

public:
	int  m_mousePosX;
	int  m_mousePosY;
	//押されているか
	bool IsTrigger(int key);
	//押された瞬間に取得
	bool IsPress(int key);
	//離した瞬間の処理
	bool IsRelease(int key);

	int m_nowKey;
	int m_lastKey;

	

};

