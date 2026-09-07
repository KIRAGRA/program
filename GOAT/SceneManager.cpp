#include "SceneManager.h"
#include <DxLib.h>
#include "SceneMain.h"
#include "TitleScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()

{
	m_nowScene = SceneType::Title;

}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_pSceneMain = new SceneMain;
	m_pTitleScene = new TitleScene;
	m_pResultScene = new ResultScene;
	m_pTitleScene->Init();
	m_pResultScene->Init();
}

void SceneManager::Update()
{
	switch (m_nowScene)
	{
	case SceneType::Title:
		m_pTitleScene->Update();
		if (m_pTitleScene->GetIsEnd())
		{
			ChangeScene(SceneType::GamePlay);
		}
		break;
	case SceneType::GamePlay:
		m_pSceneMain->Update();
		if (m_pSceneMain->GetIsEnd())
		{
			ChangeScene(SceneType::Result);
		}
		break;
	case SceneType::Result:
		m_pResultScene->Update();
		if (m_pResultScene->GetIsEnd())
		{
			ChangeScene(SceneType::Title);
		}
		break;
	default:
		break;

	}
	

}

void SceneManager::Draw()
{

	switch (m_nowScene)
	{
	case SceneType::Title:
		m_pTitleScene->Draw();
		break;
	case SceneType::GamePlay:
		m_pSceneMain->Draw();
		break;
	case SceneType::Result:
		m_pResultScene->Draw();
		break;
	default:
		break;

	}
}

void SceneManager::ChangeScene(SceneType nextscene)
{
	m_nowScene = nextscene;
	switch (m_nowScene)
	{
	case SceneType::Title:
		m_pTitleScene->Init();
		break;
	case SceneType::GamePlay:
		m_pSceneMain->Init();

		break;
	case SceneType::Result:
		m_pResultScene->Init();
		break;
	default:
		break;

	}
}
