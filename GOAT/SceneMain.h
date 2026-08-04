#pragma once
#include "Vec2.h"


class Input;
class Enemy;
class Enemy2;

class SceneMain
{
public:
	SceneMain();
	virtual~SceneMain();

	void Init();
	void Update();
	void Draw();

	bool ColCheck(Vec2 _enePos, float _halfSize);

	bool BoxColCheck(Vec2 _enePos, float _widht,float _height);



private:

	int m_score;



	Input* m_pInput;
	Enemy* m_pEnemy[1];
	Enemy2* m_pEnemy2[1];
};

