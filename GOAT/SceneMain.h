#pragma once
class Input;
class SceneMain
{
public:
	SceneMain();
	virtual~SceneMain();

	void Init();
	void Update();
	void Draw();

private:

	Input* m_pInput;

};

