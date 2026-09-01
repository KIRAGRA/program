 #include "TitleScene.h"
 #include "DxLib.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	m_isEnd = false;
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		m_isEnd = true;
	}
}

void TitleScene::Draw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Press Space Key to Start");
}
