#pragma once

class Bg;
class Car;

class MainScene
{
public:
	MainScene();

	virtual~MainScene();



	void Init();
	void Update();
	void Draw();

private:
	
	Bg* m_pBg;

	Car* m_carsH;



};

