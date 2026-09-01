#pragma once
class TitleScene
{
public:
	TitleScene();
	virtual~TitleScene();

	void Init();
	void Update();
	void Draw();

	bool GetIsEnd() { return m_isEnd; };

private:

	bool m_isEnd;

};

