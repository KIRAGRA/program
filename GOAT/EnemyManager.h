#pragma once
class Vec2;
class EnemyManager
{
public:
	EnemyManager();
	virtual~EnemyManager();



	void Init(Vec2 _pos);
	void Update();
	void Draw();
};

