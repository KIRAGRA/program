#include "Input.h"
#include <DxLib.h>
#include "GameDefine.h"
using namespace Game;

Input::Input():
	m_mousePosX(0.0),
	m_mousePosY(0.0),
	m_nowKey(0),
	m_lastKey(0)

{
}

Input::~Input()
{
}

void Input::Init()
{
	SetMousePoint(WIDTH / 2, HEIGHT / 2);
}

void Input::Update()
{
	GetMousePoint(&m_mousePosX, &m_mousePosY);
	//前のフレームに取得したマウスの情報を一つ古い状態にする
	m_lastKey = m_nowKey;
	// 現在のマウスの情報を取得する
	m_nowKey = GetMouseInput();
	


}

void Input::Draw()
{
	
}


bool Input::IsTrigger(int key)
{
	bool isNow = (m_nowKey & key);//現在のフレーム
	bool isLast = (m_lastKey & key);//前のフレーム
	
	if (isNow && !isLast)
	{
		return true;
	}

	return false;
}

//bool Input::IsPress(int key)
//{
//	if ((GetMouseInput() & MOUSE_INPUT_LEFT)!= 0)
//	{
//		DrawCircle(m_mousePosX, m_mousePosY, 8, GetColor(0, 0, 255), true);
//		printfDx("バン\n");
//	}
//	else
//	{
//
//	}
//
//	return false;
//}
