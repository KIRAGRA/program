#include "DxLib.h"
#include "GameDefine.h"
#include "stdlib.h"


//定数の定義

const int WIDTH = 1200, HEIGHT = 720;
const int FPS = 60;
const int IMG_ENEMY_MAX = 5; //敵の画像の枚数(種類)
const int BULLET_MAX = 100;//自機が発射する弾の最大数
const int ENEMY_MAX = 100;//敵機の数の最大数
const int STAGE_DISTANCE = FPS * 60;//ステージの長さ
const int PLAYER_SHIELD_MAX = 8;//自機のシールドの最大数
const int EFFECT_MAX = 100;//エフェクトの最大数
const int ITEM_TYEP = 3;//アイテムの種類
const int WEAPON_LV_MAX = 10;//武器レベルの最大値
const int PLAYER_SPEED_MAX = 20;//自機の速さの最大数
enum { ENE_BULLET, ENE_ZAKO1, ENE_ZAKO2, ENE_ZAKO3, ENE_BOSS };//敵機の種類
enum { EFF_EXPLODE, EFF_RECOVER };//エフェクトの種類
//グローバル変数
int stage = 1;
int score = 0;
int hisco = 10000;
int bossIdx = 0;//ボスを代入した配列のインデックス
int distance = 0;//ステージ終端までの距離
int weaponLv = 1;//自機の武器のレベル()
int noDamage = 0;//無敵状態

//ここでゲームに用いる変数や配列を定義する
struct OBJECT player; //自機用の構造体の変数
struct OBJECT bullet[BULLET_MAX]; //自機用の構造体の変数
struct OBJECT enemy[ENEMY_MAX];//敵機用の構造体の配列
struct OBJECT effect[EFFECT_MAX];//エフェクト用の構造体の配列
struct OBJECT item;//アイテム用の構造体変数
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
	distance = STAGE_DISTANCE;//【記述位置は仮】ステージの長さを代入

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
		if (distance > 0)distance--;//距離の計算
		DrawFormatString(0, 0, 0xffff00, "distance=%d", distance);//【仮】確認用
		if (distance % 60 == 1)//【仮】雑魚の出現
		{
			int x = 100 + rand() % (WIDTH - 200);//出現位置x座標
			int y = -50;
			int e = 1 + rand() % 2;//出現する雑魚敵の種類
			if (e == ENE_ZAKO1)setEnemy(x, y, 0, 3, ENE_ZAKO1, imgEnemy[ENE_ZAKO1], 1);
			if (e == ENE_ZAKO2)
			{
				int vx = 0;
				if (player.x < x - 50)vx = -3;
				if (player.x > x + 50)vx = 3;
				setEnemy(x, -100, vx, 5, ENE_ZAKO2, imgEnemy[ENE_ZAKO2], 3);
			}
			if (distance % 120 == 1)//【仮】雑魚機3の出現
			{
				int x = 100 + rand() % (WIDTH - 200);//出現位置	x座標
				setEnemy(x, -100, 0, 40 + rand() % 20, ENE_ZAKO3, imgEnemy[ENE_ZAKO3], 5);
			}
		}
		if (distance == 1)
		{
			bossIdx = setEnemy(WIDTH / 2, -120, 0, 1, ENE_BOSS, imgEnemy[ENE_BOSS], 200);//ボスの出現
		}
		if (distance % 800 == 1)setItem();//アイテムの出現
		moveEnemy();//敵機の出現
		movePlayer();//自機の操作
		moveBullet();//弾の制御
		drawEffect();//エフェクト
		stageMap();//ステージマップ
		drawParameter();//自機のシールドなどのパラメーターを表示


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
	player.vx = 15;
	player.vy = 15;
	player.shield = PLAYER_SHIELD_MAX;
	GetGraphSize(imgFighter, &player.wid, &player.hei);//自機の画像の幅と高さの代入
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
	if (noDamage > 0) noDamage--;
	if (noDamage % 4 < 2)drawImage(imgFighter, player.x, player.y);//自機の描画
	static char oldSpcKey;
	static int countSpcKey;
	if (CheckHitKey(KEY_INPUT_W))//上キーで上に移動
	{
		player.y -= player.vy;
		if (player.y > HEIGHT - 30)
		{
			player.y = 30;
		}
	}
	if (CheckHitKey(KEY_INPUT_S))//下キーで下に移動
	{
		player.y += player.vy;
		if (player.y > HEIGHT - 30)
		{
			player.y = HEIGHT - 30;
		}

	}
	if (CheckHitKey(KEY_INPUT_A))//左キーで左に移動
	{
		player.x -= player.vx;
		if (player.x < 30)
		{
			player.x = 30;
		}
	}
	if (CheckHitKey(KEY_INPUT_D))//右キーで右に移動
	{

		player.x += player.vx;
		if (player.x > WIDTH - 30)
		{
			player.x = WIDTH - 30;
		}
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (oldSpcKey == 0)
		{
			setBullet();
		}
		else if (countSpcKey % 20 == 0)
		{
			setBullet();
			countSpcKey++;
		}
		else
		{
			countSpcKey = 0;
		}
	}
	countSpcKey = CheckHitKey(KEY_INPUT_SPACE);

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
		char file[] = "image/enemy*.png";
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
void setBullet(void)
{
	for (int i = 0;i < BULLET_MAX; i++)
	{
		if (noDamage == 0)//無敵状態でない時、自機とヒットチェック
		{
			int dx = abs(enemy[i].x - player.x);//中心座標間のピクセル数
			int dy = abs(enemy[i].y - player.y);
			if (dx < enemy[i].wid / 2 + player.wid / 2 && dy < enemy[i].hei / 2 + player.hei / 2);
			{
				if (player.shield > 0)player.shield--;
				noDamage = FPS;//無敵状態をセット
				damageEnemy(i, 1);//敵にダメージ
			}
		}
		for (int n = 0;n < weaponLv; n++)
		{
			int x = player.x - (weaponLv - 1) * 5 + n * 10;
			int y = player.y - 20;
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (bullet[i].state == 0) //空いてる配列に弾をセットする
				{
					bullet[i].x = player.x;
					bullet[i].y = player.y - 20;
					bullet[i].vx = 0;
					bullet[i].vy = -40;//y軸方向の速さ(一回の計算で移動するピクセル数)
					bullet[i].state = 1;//弾を存在する状態にする
					break;
				}
			}

		}
		PlaySoundMem(seShot, DX_PLAYTYPE_BACK);//効果音

	}

}
void moveBullet(void)
{
	for (int i = 0;i < BULLET_MAX; i++)
	{
		if (bullet[i].state == 0)continue;//空いている配列なら処理しない
		bullet[i].x += bullet[i].vx;//　　座標を変化させる
		bullet[i].y += bullet[i].vy;//　　
		drawImage(imgBullet, bullet[i].x, bullet[i].y);//弾の描画
		if (bullet[i].y < -100)
		{
			bullet[i].state = 0;
		}

	}
}
int setEnemy(int x, int y, int vx, int vy, int ptn, int img, int sld)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].state == 0)
		{
			enemy[i].x = x;
			enemy[i].y = y;
			enemy[i].vx = vx;
			enemy[i].vy = vy;
			enemy[i].state = 1;
			enemy[i].pattern = ptn;
			enemy[i].image = img;
			enemy[i].shield = sld * stage;//ステージが進むほど敵が固くなる
			GetGraphSize(img, &enemy[i].wid, &enemy[i].hei);//画像の幅と高さを代入
			return i;
		}
	}
	return -1;

}
//敵機を動かす
void moveEnemy(void)
{
	for (int i = 0;i < ENEMY_MAX; i++)
	{
		if (enemy[i].state == 0)continue;//空いている配列なら処理しない
		if (enemy[i].pattern == ENE_ZAKO3)
		{
			if (enemy[i].vy > 1)//減速
			{
				enemy[i].vy *= 0.9;
			}

			else if (enemy[i].vy > 0)//弾発射、飛び散る
			{
				setEnemy(enemy[i].x, enemy[i].vy, 0, 6, ENE_BULLET, imgEnemy[ENE_BULLET], 0);//弾
				enemy[i].vx = 8;
				enemy[i].vy = -4;
			}
		}
		if (enemy[i].pattern == ENE_BOSS)//ボス機
		{
			if (enemy[i].y > HEIGHT - 120)enemy[i].vy = -2;
			if (enemy[i].y < 120)//画面上端
			{
				if (enemy[i].y < 0)//弾発射
				{
					for (int bx = -2; bx <= 2; bx++)
					{
						for (int by = 0;by <= 3; by++)
						{
							if (bx == 0 && by == 0)continue;
							{
								setEnemy(enemy[i].x, enemy[i].y, bx * 2, by * 3, ENE_BULLET, imgEnemy[ENE_BULLET], 0);
							}
						}
						enemy[i].vy = 2;
					}
				}


			}
		}
		enemy[i].x += enemy[i].vx;//敵機の移動
		enemy[i].y += enemy[i].vy;
		drawImage(enemy[i].image, enemy[i].x, enemy[i].y);//敵機の描画
		//画面外に出たか
		if (enemy[i].x < -200 || WIDTH + 200 < enemy[i].x || enemy[i].y < -200 || HEIGHT + 200 < enemy[i].y) enemy[i].state = 0;

		//あたり判定のアルゴリズム
		if (enemy[i].shield > 0)//ヒットチェックを行う敵機(弾以外)
		{
			for (int j = 0; j < BULLET_MAX; j++)//自機の弾とヒットチェック
			{
				if (bullet[i].state == 0)continue;
				int dx = abs((int)(enemy[i].x - bullet[j].x));//中心座標のピクセル数
				int dy = abs((int)(enemy[i].y - bullet[j].y));//中心座標のピクセル数
				if (dx < enemy[i].wid / 2 && dy < enemy[i].hei / 2);//接触してるか
				{
					bullet[j].state = 0;//弾を消す
					damageEnemy(i, 1);//敵のダメージ
				}
			}
		}

	}
}
//敵機のシールドを減らす(ダメージを与える)
void damageEnemy(int n, int dmg)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 192);//加算による描画の重ね合わせ
	DrawCircle(enemy[n].x, enemy[n].y, (enemy[n].wid + enemy[n].hei) / 4, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードの解除
	score += 100;//スコアの加算
	if (score > hisco)hisco = score;//ハイスコアの更新
	enemy[n].shield -= dmg;//シールドを減らす
	if (enemy[n].shield <= 0)
	{
		enemy[n].state = 0;//シールド0以下で消す
		setEffect(enemy[n].x, enemy[n].y, EFF_EXPLODE);//爆発演出
	}

}
void stageMap(void)
{
	int mx = WIDTH - 30, my = 60;//マップの表示
	int wi = 20, he = HEIGHT - 120;//マップの高さ
	int pos = (HEIGHT - 140) * distance / STAGE_DISTANCE;//自機の飛行している位置
	SetDrawBlendMode(DX_BLENDMODE_SUB, 128);//減算による描画の重ね合わせ
	DrawBox(mx, my, mx + wi, my + he, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードを解除
	DrawBox(mx - 1, my - 1, mx + wi + 1, my + he + 1, 0xffffff, false);//枠線
	DrawBox(mx, my + pos, mx + wi, my + pos + 20, 0x0080ff, true);//自機の位置

}
void drawText(int x, int y, const char* txt, int val, int col, int siz)
{
	SetFontSize(siz);//フォントの大きさを指定
	DrawFormatString(x + 1, y + 1, 0x00000, txt, val);//黒で文字列を表示
	DrawFormatString(x, y, col, txt, val);//引数の色で文字列を表示 
}
void drawParameter(void)
{
	int x = 10, y = HEIGHT - 30;//表示位置
	DrawBox(x, y, x + PLAYER_SHIELD_MAX * 30, y + 20, 0x000000, true);
	for (int i = 0;i < player.shield; i++)//シールドのメーター
	{
		int r = 128 * (PLAYER_SHIELD_MAX - i) / PLAYER_SHIELD_MAX;//RGB値計算
		int g = 255 * i / PLAYER_SHIELD_MAX;
		int b = 160 + 96 * i / PLAYER_SHIELD_MAX;
		DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y + 18, GetColor(r, g, b), true);
	}
	drawText(x, y - 25, "SHIELD Lv %02d", player.shield, 0xffffff, 20);//シールド値
	drawText(x, y - 50, "WEAPON Lv %02d", weaponLv, 0xffffff, 20);//シールド値
	drawText(x, y - 75, "SPEED %02d", player.vx, 0xffffff, 20);//シールド値
}
void setEffect(int x, int y, int ptn)
{
	static int eff_num;
	effect[eff_num].x = x;
	effect[eff_num].y = y;
	effect[eff_num].state = 1;
	effect[eff_num].pattern = ptn;
	effect[eff_num].timer = 0;
	eff_num = (eff_num + 1) % EFFECT_MAX;
	if (ptn == EFF_EXPLODE)PlaySoundMem(seExpl, DX_PLAYTYPE_BACK);//効果音
}
void drawEffect(void)
{
	int ix;
	for (int i = 0;i < EFFECT_MAX; i++)
	{
		if (effect[i].state == 0)continue;
		switch (effect[i].pattern)//エフェクトごとに処理をわける
		{
		case EFF_EXPLODE: //爆発演出
			ix = effect[i].timer * 128;//画像の切り出し
			DrawRectGraph(effect[i].x - 64, effect[i].y - 64, ix, 0, 128, 128, imgExplosion, true, false);
			effect[i].timer++;
			if (effect[i].timer == 7)effect[i].state = 0;
			break;

		case EFF_RECOVER://回復演出
			if (effect[i].timer < 30)//加算による描画の重ね合わせ
				SetDrawBlendMode(DX_BLENDMODE_ADD, effect[i].timer * 8);
			else
				SetDrawBlendMode(DX_BLENDMODE_ADD, (60 - effect[i].timer) * 8);
			for (int i = 3;i < 8; i++)DrawCircle(player.x, player.y, (player.wid + player.hei) / i, 0x2040c0, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードを解除
			effect[i].timer++;
			if (effect[i].timer == 60)effect[i].state = 0;
			//アイテムを組み込む時に記述
			break;
		}
	}

}
void setItem(void)
{
	item.x = (WIDTH / 4) * (1 + rand() % 3);
	item.y = -16;
	item.vx = 15;
	item.vy = 1;
	item.state = 1;
	item.timer = 0;
}
//アイテム処理
void moveItem(void)
{
	if (item.state == 0)return;
	item.x += item.vx;
	item.y += item.vy;
	if (item.timer % 60 < 30)
	{
		item.vx -= 1;
	}
	else
	{
		item.vx += 1;
	}
	if (item.y > HEIGHT + 16)item.state = 0;
	item.pattern = (item.timer / 120) % ITEM_TYEP;//現在、どのアイテムになっているか
	item.timer++;
	DrawRectGraph(item.x - 20, item.y - 16, item.pattern * 40, 0, 40, 32, imgItem, true, false);
	//if(scene == OVER)
	int dis = (item.x - player.x) * (item.x - player.x) + (item.y - player.y) * (item.y - player.y);
	if (dis < 60 * 60)//アイテムと自機とのヒットチェック(円による当たり判定)
	{
		item.state = 0;
		if (item.pattern == 0)//スピードアップ
		{
			if (player.vx < PLAYER_SPEED_MAX)
			{
				player.vx += 3;
				player.vy += 3;
			}
		}
		if (item.pattern == 1)//シールド回復
		{
			if (player.shield < PLAYER_SHIELD_MAX)player.shield++;
			setEffect(player.x, player.y, EFF_RECOVER);//回復エフェクトを表示
		}
		if (item.pattern == 2)//武器レベルアップ
		{
			if (weaponLv < WEAPON_LV_MAX)weaponLv++;
		}
		PlaySoundMem(seItem, DX_PLAYTYPE_BACK);//効果音
	}
}
