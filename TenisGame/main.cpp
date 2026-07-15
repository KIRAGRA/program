#include "DxLib.h"
#include <stdlib.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const int WIDTH = 960, HEIGHT = 640;

	ChangeWindowMode(1);          // windowモードで起動
	SetGraphMode(WIDTH, HEIGHT, 32);  // ウィンドウサイズを16：9に
	SetMainWindowText("DxLibTemplate"); // ウィンドウのタイトル表示を変更

	if (DxLib_Init() == -1)       // ＤＸライブラリ初期化処理
	{
		return -1;                // エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//ボールを動かすための変数
	int ballX = 40;
	int ballY = 80;
	int ballVx = 5;
	int ballVy = 5;
	int ballR = 10;

	//ラケットを動かすための変数
	int racketX = WIDTH / 2;
	int racketY = HEIGHT - 50;
	int racketW = 120;
	int racketH = 12;


	int fpsCount = 0;
	int currentFps = 0;
	int startTime = GetNowCount();
	int totalFrames = 0;

	//ゲーム進行に関する変数、スコアを代入する変数
	enum{TITLE,PLAY,OVER};
	int scene = TITLE;
	int timer = 0;
	int score = 0;//スコア
	int highScore = 1000;//ハイスコア
	int dx, dy;//ヒットチェック


	while (ProcessMessage() == 0)
	{
		// 1フレームの開始時間を高精度で取得
		LONGLONG start = GetNowHiPerformanceCount();
		timer++;
		ClearDrawScreen();

		switch (scene)
		{
		case TITLE://タイトル画面の処理
			SetFontSize(50);
			DrawString(WIDTH / 2 - 50 / 2 * 12 / 2, HEIGHT / 3, "Tenis Game", GetColor(255, 0, 255));
			if (timer % 60 < 30) {
				SetFontSize(30);
				DrawString(WIDTH / 2 - 30 / 2 * 21 / 2, HEIGHT * 2 / 3, "Press Space to start.", GetColor(255, 0, 255));
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)//スペースキー押し下し
			{
				ballX = 40;
				ballY = 80;
				ballVx = 5;
				ballVy = 5;
				racketX = WIDTH / 2;
				racketY = HEIGHT - 50;
				score = 0;
				scene = PLAY;
			}
			break;

		case PLAY: //ゲームをプレイする処理
			//ボールの処理
			ballX = ballX + ballVx;
			if (ballX < ballR && ballVx < 0)ballVx = -ballVx;
			if (ballX > WIDTH - ballR && ballVx > 0)ballVx = -ballVx;
			ballY = ballY + ballVy;
			if (ballY < ballR && ballVy < 0)ballVy = -ballVy;
			if (ballY > HEIGHT)
			{
				scene = OVER;
				timer = 0;
				break;
			}

			//ボールの処理
			ballX = ballX + ballVx;
			if (ballX < ballR && ballVx < 0)ballVx = -ballVx;
			if (ballX > WIDTH - ballR && ballVx > 0)ballVx = -ballVx;
			ballY = ballY + ballVy;
			if (ballY < ballR && ballVy < 0)ballVy = -ballVy;
			if (ballY > HEIGHT && ballVy > 0)ballVy = -ballVy;
			DrawCircle(ballX, ballY, ballR, GetColor(255, 0, 255), TRUE);//ボール

			//ラケットの処理
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)//左キー押し下し
			{
				racketX = racketX - 10;
				if (racketX < racketW / 2)racketX = racketW / 2;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)//右キー押し下し
			{
				racketX = racketX + 10;
				if (racketX > WIDTH - racketW / 2)racketX = WIDTH - racketW / 2;
			}
			DrawBox(racketX - racketW / 2, racketY - racketH / 2, racketX + racketW / 2, racketY + racketH / 2, GetColor(255, 0, 255), TRUE);//ラケット



			//ヒットチェック
			dx = ballX - racketX;//x軸方向の距離
			dy = ballY - racketY;//y軸方向の距離
			if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0)
			{
				ballVy = -5 - rand() % 5;
				score = score + 100;
				if (score > highScore)highScore = score;//ハイスコアの更新
			}
			break;

		case OVER://ゲームオーバーの処理
			SetFontSize(40);
			DrawString(WIDTH / 2 - 40 / 2 * 9 / 2, HEIGHT / 3, "GAME OVER", GetColor(255,0, 255));
			if (timer > 60 * 5)scene = TITLE;
			break;

		}

		SetFontSize(30);
<<<<<<< Updated upstream
		//DrawFormatString(10, 10, GetColor(255, 0, 255));
=======
		DrawFormatString(120, 120, GetColor(255, 0, 255),"SCORE %d" , score);
		DrawFormatString(WIDTH - 200, 10, GetColor(255, 0, 255), "HI-SC %d", highScore);
>>>>>>> Stashed changes
			

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