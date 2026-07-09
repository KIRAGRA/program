#pragma once
#include "Player.h"
#include "Item.h"
#include "Bg.h"
#include "Trap.h"
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();


	void Update();
	void Draw();

private:


	int GetItemNum() const;
	
private:
	static const int kItemNum = 15;
	
private:
	int m_playerIdleHandle;
	int m_playerRunHandle;
	int m_itemHandle;
	int m_trapHandle;

	//サウンドリソースのハンドル
	int m_bgmHandle;
	int m_hitSeHandle;

	//フォントのハンドル
	int m_uiFontHandle;

	//フェード処理
	int m_fadeAlpha;
	int m_fadeSpeed;

	

	int m_frameCount;

	//ゲームオーバーになったか？
	bool m_isGameover;

	Player m_player;
	Item m_item[kItemNum];
	Bg m_bg;
	Trap m_trap;

};

