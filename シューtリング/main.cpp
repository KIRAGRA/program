#include "DxLib.h"
#include "GameDefine.h"


//定数の定義
const int WIDTH = 1200,HEIGHT = 720;
const int FPS = 60;
const int IMG_ENEMY_MAX = 5; //敵の画像の枚数(種類)
//グローバル変数
//ここでゲームに用いる変数や配列を定義する
struct OBJECT player; //自機用の構造体の変数
int imgGalaxy, imgFloor, imgWallL, imgWallR;//背景画像
int imgFighter, imgBullet;//自機と自機の弾の画像
int imgEnemy[IMG_ENEMY_MAX];//敵機の画像
int imgExplosion;//爆発演出の画像
int imgItem;//アイテムの画像
int bgm, jinOver, jinClear, seExpl, seItem, seShot;//音の読み込み用





int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(1);          // windowモードで起動
	SetGraphMode(WIDTH, HEIGHT, 32);  // ウィンドウサイズを16：9に
	SetMainWindowText("DxLibTemplate"); // ウィンドウのタイトル表示を変更
	
	if (DxLib_Init() == -1)       // ＤＸライブラリ初期化処理
	{
		return -1;                // エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	initGame();//初期化の関数を呼び出す
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);//【仮】BGMの出力

	int fpsCount = 0;
	int currentFps = 0;
	int startTime = GetNowCount();
	int totalFrames = 0;
	initGame(); //初期化用の関数を呼び出す
	initVariable();//【仮】ゲームを完成させる際に呼び出し位置を変える

	while (ProcessMessage() == 0)
	{
		// 1フレームの開始時間を高精度で取得
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();

		//ゲームの骨組みとなる処理を、ここに記述する
		DrawGraph(0, 0, imgGalaxy, FALSE);//【仮】星空を表示

		// 画面にFPSを表示
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS: %d", currentFps);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "Total Frames: %d", totalFrames);

		scrollBG(1);//【仮】背景スクロール
		movePlayer();//自機の操作

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

//ゲーム開始時の初期値を代入する関数
void initVariable(void)
{
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.vx = 5;
	player.vy = 5;
}

//中心座標を指定して画像を表示する関数
void drawImage(int img, int x, int y)
{
	int w, h;
	GetGraphSize(img, &w, &h);
	DrawGraph(x - w / 2, y - h / 2, img, true);
}

//自機を動かす関数
void movePlayer(void)
{
	if (CheckHitKey(KEY_INPUT_UP))//上キーで上に移動
	{
		player.y -= player.vy;
		if (player.y > HEIGHT - 30)player.y = 30;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))//下キーで下に移動
	{
		player.y += player.vy;
		if (player.y > HEIGHT - 30)player.y = HEIGHT - 30;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))//左キーで左に移動
	{
		player.x -= player.vx;
		if (player.x < 30)
		{
			player.x = 30;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))//右キーで右に移動
	{
		player.x += player.vx;
		if (player.x > WIDTH - 30)
		{
			player.x = WIDTH - 30;
		}
	}
	drawImage(imgFighter, player.x, player.y);//自機の描画
}

void initGame(void)
{
	//背景用の画像を読み込み
	imgGalaxy = LoadGraph("image/bg0.png");
	imgFloor = LoadGraph("image/bg1.png");
	imgWallL = LoadGraph("image/bg2.png");
	imgWallR = LoadGraph("image/bg3.png");

	//自機と自機の弾を画像の読み込み
	imgFighter = LoadGraph("image/fighter.png");
	imgBullet = LoadGraph("image/bullet.png");
	//敵機の画像の読み込み
	for (int i = 0; i < IMG_ENEMY_MAX; i++)
	{
		char file[] = "image/enemy.png";
		file[11] = (char)('0' + i);
		imgEnemy[i] = LoadGraph(file);
	}
	imgExplosion = LoadGraph("image/explosion.png");//爆発演出
	imgItem = LoadGraph("image/item.png");//アイテム

	bgm = LoadSoundMem("sound/bgm.mp.3");
	jinOver = LoadSoundMem("sound/gameover.mp3");
	jinClear = LoadSoundMem("sound/stageclear.mp3");
	seExpl = LoadSoundMem("sound/explosion.mp3");
	seItem = LoadSoundMem("sound/item.mp3");
	seShot = LoadSoundMem("sound/shot.mp3");
	ChangeVolumeSoundMem(128, bgm);
	ChangeVolumeSoundMem(128, jinOver);
	ChangeVolumeSoundMem(128, jinClear);
}
void scrollBG(int spd)
{
	static int galaxyY, floorY, wallY;//スクロール位置を管理する変数(静的記憶領域に保持される)
	galaxyY = (galaxyY + spd) % HEIGHT;//星空(宇宙)
	DrawGraph(0, galaxyY - HEIGHT, imgGalaxy, false);
	DrawGraph(0, galaxyY, imgGalaxy, false);
	floorY = (floorY + spd * 2) % 120;//床
	for (int i = -1; i < 6;i++)DrawGraph(240, floorY + i * 120, imgFloor, true);
	wallY = (wallY + spd * 4) % 240;
	DrawGraph(0, wallY - 240, imgWallL, true);
	DrawGraph(WIDTH - 300, wallY - 240, imgWallR, true);
}