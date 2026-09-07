#pragma once
class ResultScene
{
public:
	ResultScene();
	virtual~ResultScene();

	void Init();
	void Update();
	void Draw();

	bool GetIsEnd() { return m_isEnd; };

private:
	bool m_isEnd;

	
};

