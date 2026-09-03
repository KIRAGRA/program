#pragma once

enum SceneType
{
	Title,
	GamePlay,
	Result

};


class SceneManager
{
	SceneManager();
	virtual~SceneManager();

	void Init();
	void Update();
	void Draw();

	void ChangeScene(SceneType nextscene);

private:
	 
	SceneType m_nowScene;


};

