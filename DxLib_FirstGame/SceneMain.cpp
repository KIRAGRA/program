#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"
#include "Item.h"
#include "Trap.h"

SceneMain::SceneMain() :
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_itemHandle(-1),
	m_trapHandle(-1),
	m_hitSeHandle(-1),
	m_fadeAlpha(0),
	m_fadeSpeed(-1),
	m_frameCount(0),
	m_bgmHandle(-1),
	m_uiFontHandle(0),
	m_isGameover(false)

{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//シーン内で使用するリソースのロード
	m_playerIdleHandle = LoadGraph("image/idle.png");
	m_playerRunHandle = LoadGraph("image/run.png");
	m_itemHandle = LoadGraph("image/Apple.png");
	m_trapHandle = LoadGraph("image/Saw.png");

	//サウンドのロード
	m_hitSeHandle = LoadSoundMem("image/hit.mp3");
	m_bgmHandle = LoadSoundMem("image/bgm.mp3");

	//フォントの作成
	m_uiFontHandle = CreateFontToHandle("Magneto", 48 - 1, -1);

	m_frameCount = 0;
	m_bg.Init();
	m_player.Init();
	for (int i = 0; i < kItemNum; i++)
	{
		m_item[i].SetHandle(m_itemHandle);
		m_item[i].Init();
	}

	m_trap.SetHandle(m_trapHandle);
	m_trap.Init();
	
	//フェードイン開始
	m_fadeAlpha = 255;
	m_fadeSpeed = -8;

	//BGMを鳴らし始める
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);


}

void SceneMain::End()
{
	//BGMの停止
	StopSoundMem(m_bgmHandle);
	m_bg.End();
	m_player.End();
	m_trap.End();
	for (int i = 0; i < kItemNum; i++)
	{
		m_item[i].End();
	}



	DeleteGraph(m_playerIdleHandle);
	DeleteGraph(m_playerRunHandle);
	DeleteGraph(m_itemHandle);
	DeleteGraph(m_trapHandle);
	DeleteSoundMem(m_hitSeHandle);
	
	//フォントをメモリから削除
	DeleteFontToHandle(m_uiFontHandle);
	
}

void SceneMain::Update()

{
	m_frameCount++;
	//フェード処理
	m_fadeAlpha += m_fadeSpeed;
	if (m_fadeAlpha < 0)
	{
		//フェードアウト終了
		m_fadeAlpha = 0;
		m_fadeSpeed = 0;
	}
	if (m_fadeAlpha > 255)
	{
		//フェード終了
		m_fadeAlpha = 255;
		m_fadeSpeed = 255;
	}

	m_bg.Update();
	m_trap.Update();
	
	m_player.Update();
	for (int i = 0; i < kItemNum; i++)
	{
		m_item[i].Update();
	}
	for (int i = 0; i < kItemNum; i++)
	{
		if (!m_item[i].IsExist()) continue;
		float dx = m_player.GetColCenterX() - m_item[i].GetColCenterX();
		float dy = m_player.GetColCenterY() - m_item[i].GetColCenterY();
		float sqDist = (dx * dx) + (dy * dy);

		float sumRadius = m_player.GetRadius() + m_item[i].GetRadius();
		if (sqDist < (sumRadius * sumRadius))
		{
			//当たった処理
			m_item[i].OnHit();

			//PlaySoundFile("sound/hit.mp3", DX_PLAYTYPE_NORMAL);
			PlaySoundMem(m_hitSeHandle, DX_PLAYTYPE_BACK);
		}
	}

	//プレイヤーと敵の当たり判定
	{
		float dx = m_player.GetColCenterX() - m_trap.GetColCenterX();
		float dy = m_player.GetColCenterY() - m_trap.GetColCenterY();
		float sqDist = (dx * dx) + (dy * dy);

		float sumRadius = m_player.GetRadius() + m_trap.GetRadius();
		if (sqDist < (sumRadius * sumRadius))
		{
		//	printf("のこぎりに当たっている\n");
			m_isGameover = true;
			m_player.OnDead();
		}
		
	}



	//アイテムをすべてチェックして、存在するアイテムがない場合はゲームを終了する処理
	int itemNum = 0;
	for (int i = 0; i < kItemNum; i++)
	{
		if (m_item[i].IsExist())
		{
			itemNum++;
		}
	}
	if (GetItemNum() <= 0)
	{
		m_fadeSpeed = 8;
		
	}

}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_player.Draw();
	m_trap.Draw();
	for (int i = 0; i < kItemNum; i++)
	{
		m_item[i].Draw();
	}

		//UIの表示UIはゲームの最前面に表示される
	int uiWidth = GetDrawFormatStringWidthToHandle(m_uiFontHandle, "%d", GetItemNum());
	//DrawFormatString(Game::kScreenWidth / 2, 8, GetColor(0, 0, 0), "%d", GetItemNum());
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 2 - uiWidth / 2, 2+8, GetColor(192, 192, 192), m_uiFontHandle, "%d", GetItemNum());
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - uiWidth / 2 , 8, GetColor(255, 32, 32),m_uiFontHandle, "%d", GetItemNum());

	//ゲームオーバー表示
	if (m_isGameover)
	{
		int width = GetDrawStringWidthToHandle("GAME OVER!" ,strlen("GSME OVER!"), m_uiFontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, 200, "GAME OVER!", GetColor(200, 2000, 200), m_uiFontHandle);
	}


	//int itemNum = 0;
	//for (int i = 0; i < kItemNum; i++)
	//{
	//	if (m_item[i].IsExist())
	//	{
	//		itemNum++;
	//	}
	//}
	

	//フェード処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	

	DrawString(0,0,"SceneMain",GetColor(255, 255, 255));
	DrawString(0,32,"",GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(0, 255, 0), "FRAME:%d", m_frameCount);
	
	
}

int SceneMain::GetItemNum() const
{
	int itemNum = 0;//存在するアイテムの数
	for (int i = 0; i < kItemNum; i++)
	{
		if (m_item[i].IsExist())
		{
			itemNum++;

		}
	}
	
	
	return itemNum;

}
