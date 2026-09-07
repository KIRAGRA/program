#pragma once

class SceneMain;
class TitleScene;
class ResultScene;
enum SceneType
{
	Title,
	GamePlay,
	Result

};


class SceneManager
{
public:
	

	void ChangeScene(SceneType nextscene);SceneManager();
	virtual~SceneManager();

	void Init();
	void Update();
	void Draw();

private:
	 
	SceneType m_nowScene;

	SceneMain* m_pSceneMain;

	TitleScene* m_pTitleScene;

	ResultScene* m_pResultScene;

};

