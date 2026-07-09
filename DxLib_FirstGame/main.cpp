#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//Windowモードで起動
	ChangeWindowMode(1);

	//ウィンドウサイズを16:9にする
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	//ウィンドウのタイトル表示を変更
	SetMainWindowText("DxLibTemplate");



	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームシーンの作成
	SceneMain scene;
	scene.Init();

	while (ProcessMessage() == 0)
	{
		//現在のフレームの開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();


		//画面をクリア
		ClearDrawScreen();



		//ゲームの処理
		scene.Update();

		scene.Draw();
		

		//画面の書き換えを待つ
		ScreenFlip();

		//escキーが押したらゲームを強制終了

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
		

		//画面外のリフレッシュレートにかかわらず1/60経過するまで待つ
		while(GetNowHiPerformanceCount() - start < 16667)
		{
			//経過時間まで何もせずに待つ
		}


	}



	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}