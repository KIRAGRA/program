#pragma once
namespace Pad
{
	//更新処理
	void Update();
	//押されているか
	bool IsPress(int key);
	//押された瞬間の取得
	bool IsTrigger(int key);
	//話した瞬間を取得
	bool IsRelease(int key);
}
class Pad
{

};

