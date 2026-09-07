#include "ResultScene.h"
#include <DxLib.h>
ResultScene::ResultScene()

{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	m_isEnd = false;

	
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_R) == 1)
	{
		m_isEnd = true;
	}
}

void ResultScene::Draw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Press R Key to Start");
}
