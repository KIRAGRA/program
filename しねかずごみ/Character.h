#pragma once

class Character
{
public:
	Character();
	virtual~Character();

	void Init();
	void Update();
	void Draw();

public:
	int m_handle;
};

