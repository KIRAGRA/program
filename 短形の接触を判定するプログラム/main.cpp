#include "DxLib.h"
#include<stdlib.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const int WIDTH = 960, HEIGHT = 640;
	const int WHITE = GetColor(255, 255, 255);



	ChangeWindowMode(1);          // windowモードで起動
	SetGraphMode(WIDTH, HEIGHT, 32);  // ウィンドウサイズを16：9に
	SetMainWindowText("DxLibTemplate"); // ウィンドウのタイトル表示を変更

	if (DxLib_Init() == -1)       // ＤＸライブラリ初期化処理
	{
		return -1;                // エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int x1 = 0, y1 = 0, w1 = 120, h1 = 80;
	int x2 = WIDTH / 2, y2 = HEIGHT / 2, w2 = 160, h2 = 240;

	int fpsCount = 0;
	int currentFps = 0;
	int startTime = GetNowCount();
	int totalFrames = 0;

	while (ProcessMessage() == 0)
	{
		// 1フレームの開始時間を高精度で取得
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();

		GetMousePoint(&x1, &y1);
		int col1 = GetColor(255, 0, 0);
		int col2 = GetColor(0, 0, 255);
		int dx = abs((x1 - x2));
		int dy = abs((y1 - y2));
		if (dx <= (w1 + w2) / 2 && dy <= (h1 + h2) / 2)//ヒットチェック
		{
			col1 = GetColor(255, 255, 0);
			col2 = GetColor(0, 255, 255);
		}
		DrawBox(x1 - w1 / 2, y1 - h1 / 2, x1 + w1 / 2, y1 + h1 / 2, col1, TRUE);
		DrawBox(x2 - w2 / 2, y2 - h2 / 2, x2 + w2 / 2, y2 + h2 / 2, col2, TRUE);




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