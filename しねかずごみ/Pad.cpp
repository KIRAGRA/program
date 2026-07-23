#include "Pad.h"
#include <DxLib.h>

namespace 
{
	//前フレームのパッド押し下げ状態
	int lastPad = 0;
	//このフレームのパッドの押し下げ状態
	int nowPad = 0;
}
namespace Pad
{	
	void Update()
	{
		//前のフレームに取得したパッド情報を一つ古い状態にする
		lastPad = nowPad;

		//現在のパッドの情報も取得する
		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	bool Pad::IsPress(int key)
	{
		//現在のフレームで押されている
		return (nowPad & key);
	}

	bool Pad::IsTrigger(int key)
	{
		bool isNow = (nowPad & key);//現在のフレーム
		bool isLast = (lastPad & key);//前のフレーム

		if (isNow && !isLast)
		{
			return true;
		}
		return false;
	}

	bool Pad::IsRelease(int key)
	{
		bool isNow = (nowPad & key);//現在のフレーム
		bool isLast = (lastPad & key);//前のフレーム

		if (isNow && !isLast)
		{
			return true;
		}
		return false;
	}

}