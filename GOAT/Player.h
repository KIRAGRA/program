#pragma once
class Player
{
public:
	Player();
	virtual~Player();

	void Init();
	void Update();
	void End();

private:

	int m_bulletAttack;

};

