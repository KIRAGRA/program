#pragma once

class Input
{
public:
	Input();
	virtual~Input();

	void Init();
	void Update();
	void Draw();

	

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

