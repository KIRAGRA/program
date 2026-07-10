#pragma once
class Bg
{
public:
	Bg();
	virtual~Bg();

	void Init();
	void Update();
	void Draw();

private:
	//背景Handle
	int m_bgH;

	//背景スクロールのための変数
	int m_bgY;


};

