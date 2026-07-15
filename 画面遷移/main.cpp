#include "DxLib.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	const int WIDTH = 960, HEIGHT = 640; //ウィンドウの幅と高さのピクセル
	const int WHITE = GetColor(255, 255, 255);//よく使う色の定義
	const int RED = GetColor(255, 0, 0);//赤い色の定義


	ChangeWindowMode(1);          // windowモードで起動
	SetGraphMode(1280, 720, 32);  // ウィンドウサイズを16：9に
	SetMainWindowText("DxLibTemplate"); // ウィンドウのタイトル表示を変更

	if (DxLib_Init() == -1)       // ＤＸライブラリ初期化処理
	{
		return -1;                // エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0; //経過時間を数える
	enum { TITLE, PLAY, MENU, CLEAR, OVER };//各シーンを定める
	int scene = TITLE;//どのシーンの処理を行うか

	int fpsCount = 0;
	int currentFps = 0;
	int startTime = GetNowCount();
	int totalFrames = 0;

	while (ProcessMessage() == 0)
	{
		// 1フレームの開始時間を高精度で取得
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();
		timer++;//時間のカウント
		SetFontSize(16);
		DrawFormatString(0, 0, WHITE, "%d", timer);

		switch (scene)//画面遷移を行うswitch文
		{

		case TITLE: //タイトル画面処理
			SetFontSize(50);
			DrawString(100, 50, "タイトル画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Sキーを押すとゲーム開始", WHITE);
			if (CheckHitKey(KEY_INPUT_S) == 1)scene = PLAY;
			break;

		case PLAY: //ゲームをプレイする処理
			SetFontSize(50);
			DrawString(100, 50, "ゲーム開始", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Mキーでメニュー画面へ", WHITE);
			SetFontSize(20);
			DrawString(100, 300, "Oキーでゲームオーバー", RED);
			if (CheckHitKey(KEY_INPUT_M) == 1)scene = MENU;
			if (CheckHitKey(KEY_INPUT_O) == 1)
			{
				scene = OVER;
				timer = 0;
			}
			break;

		case MENU: //メニュー画面処理
			SetFontSize(50);
			DrawString(100, 50, "メニュー画面", WHITE);
			SetFontSize(20);
			DrawString(100, 200, "Rキーでゲームに戻る", WHITE);
			if (CheckHitKey(KEY_INPUT_R) == 1)scene = PLAY;
			break;

		case CLEAR: //ゲームクリア処理

			break;

		case OVER: //ゲームオーバー処理
			SetFontSize(50);
			DrawString(100, 50, "GAME OVER", RED);
			DrawString(100, 200, "Sキーを押すとゲーム開始", WHITE);
			if (timer > 30 * 5)scene = TITLE;
			break;


		}


			// 画面にFPSを表示
			DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS: %d", currentFps);
			DrawFormatString(0, 20, GetColor(255, 255, 255), "Total Frames: %d", totalFrames);

			ScreenFlip();

			fpsCount++;
			totalFrames++;

			if (GetNowCount() - startTime >= 1000)
			{
				currentFps = fpsCount;
				fpsCount = 0;
				startTime += 1000;
			}

			// Escapeキーが押されたらループを抜ける
			if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

			// 60FPS（約16.6ms）を維持するためのウエイト処理
			while (GetNowHiPerformanceCount() - start < 16667) Sleep(0);
		}

		DxLib_End();                   // ＤＸライブラリ使用の終了処理
		return 0;                      // ソフトの終了 
	
}
