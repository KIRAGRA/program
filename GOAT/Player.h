#pragma once
class Player
{
public:
	Player();
	virtual~Player();

	void Init();
	void Update();
	void Draw();

private:

	int m_bulletAttack;


	int m_playerHandle;

	int m_animFrame;

	int m_tinkoPos;
};

