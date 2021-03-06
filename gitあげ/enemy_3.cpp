//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "player.h"
#include "map.h"
#include <time.h>
#include "sound.h"
#include "timer.h"
#include "patrol.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_SPD			(1.4f)
#define ENEMY_SIZE			(55.0f)
#define SERCH_RANGE			(220.0f)
#define FIND_SPD			(2.0f)
#define NONE_MOVE			(150.0f)

// 初期位置管理用
#define ROOT_NUM			(2)
#define ROOT_NUM2			(0)
#define ROOT_NUM3			(8)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void SetEnemy3(int i);
void WatchEnemy3(int i);
void NoneWatchEnemy3(int i);
bool SerchPlayer3(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
unsigned char	g_EnemyTexture3 = 0;
unsigned char	g_watch_SE3 = 0;
unsigned char	g_watch_lost_SE3 = 0;

// メモリ確保用アドレス
ENEMY* g_Enemy3;		  // エネミー構造体
char* g_Route3X_1;		  // 巡回ルート用
char* g_Route3Y_1;		  // 巡回ルート用

char* g_Route3X_2;		  // 巡回ルート用
char* g_Route3Y_2;		  // 巡回ルート用

char* g_Route3X_3;		  // 巡回ルート用
char* g_Route3Y_3;		  // 巡回ルート用

char* g_Route3X_4;		  // 巡回ルート用
char* g_Route3Y_4;		  // 巡回ルート用

char* g_Route3X_5;		  // 巡回ルート用
char* g_Route3Y_5;		  // 巡回ルート用

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy3(void)
{
	g_EnemyTexture3 = LoadTexture("data/TEXTURE/enemy.png");
	g_watch_SE3 = LoadSound("data/SE/watch1.wav");
	g_watch_lost_SE3 = LoadSound("data/SE/enemy_worp.wav");

	// メモリ確保
	g_Enemy3 = new ENEMY[ENEMY_MAX3];

	g_Route3X_1 = new char[ROOT_MAX3_1];
	g_Route3Y_1 = new char[ROOT_MAX3_1];

	g_Route3X_2 = new char[ROOT_MAX3_2];
	g_Route3Y_2 = new char[ROOT_MAX3_2];

	g_Route3X_3 = new char[ROOT_MAX3_3];
	g_Route3Y_3 = new char[ROOT_MAX3_3];

	g_Route3X_4 = new char[ROOT_MAX3_4];
	g_Route3Y_4 = new char[ROOT_MAX3_4];

	g_Route3X_5 = new char[ROOT_MAX3_5];
	g_Route3Y_5 = new char[ROOT_MAX3_5];
	// エネミー構造体の初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 一体目
		if (i == 0)
		{
			g_Enemy3[i].use = true;
			g_Enemy3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 23;
			g_Enemy3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 26;
			g_Enemy3[i].routenom = 3;
		}
		// 二体目
		if (i == 1)
		{
			g_Enemy3[i].use = false;
			g_Enemy3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 15;
			g_Enemy3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 13;
			g_Enemy3[i].routenom = 0;
		}
		// 三体目
		if (i == 2)
		{
			g_Enemy3[i].use = false;
			g_Enemy3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 17;
			g_Enemy3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 3;
			g_Enemy3[i].routenom = 8;
		}
		// 四体目
		if (i == 3)
		{
			g_Enemy3[i].use = false;
			g_Enemy3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 7;
			g_Enemy3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 23;
			g_Enemy3[i].routenom = 8;
		}
		// 五体目
		if (i == 4)
		{
			g_Enemy3[i].use = false;
			g_Enemy3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 10;
			g_Enemy3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 34;
			g_Enemy3[i].routenom = 8;
		}

		// 共通
		g_Enemy3[i].watch = false;
		g_Enemy3[i].w = ENEMY_SIZE;
		g_Enemy3[i].h = ENEMY_SIZE;
		g_Enemy3[i].vel = D3DXVECTOR2(ENEMY_SPD, ENEMY_SPD);
		g_Enemy3[i].notmove = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy3[i].addmove = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy3[i].movecntX = false;
		g_Enemy3[i].movecntY = false;

		// エネミーUV
		g_Enemy3[i].u = 0.0f;
		g_Enemy3[i].v = 0.0f;
		g_Enemy3[i].uh = 0.5f;
		g_Enemy3[i].vh = 0.5f;

	}

	// 巡回ルート設定
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_Route3X_1[r] = SetRoute3X_1(r);
		g_Route3Y_1[r] = SetRoute3Y_1(r);
	}
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_Route3X_2[r] = SetRoute3X_2(r);
		g_Route3Y_2[r] = SetRoute3Y_2(r);
	}
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_Route3X_3[r] = SetRoute3X_3(r);
		g_Route3Y_3[r] = SetRoute3Y_3(r);
	}
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_Route3X_4[r] = SetRoute3X_4(r);
		g_Route3Y_4[r] = SetRoute3Y_4(r);
	}
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_Route3X_5[r] = SetRoute3X_5(r);
		g_Route3Y_5[r] = SetRoute3Y_5(r);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy3(void)
{
	// メモリ解放
	delete[] g_Enemy3;
	delete[] g_Route3X_1;
	delete[] g_Route3Y_1;
	delete[] g_Route3X_2;
	delete[] g_Route3Y_2;
	delete[] g_Route3X_3;
	delete[] g_Route3Y_3;
	delete[] g_Route3X_4;
	delete[] g_Route3Y_4;
	delete[] g_Route3X_5;
	delete[] g_Route3Y_5;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy3(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy3[i].use == true)
		{
			// 追跡判定
			if (SerchPlayer3(GetPlayerPosition(), g_Enemy3[i].pos))
			{// 見つけた(範囲内に入った)

				if (!g_Enemy3[i].watch)
				{
					PlaySound(g_watch_SE3, 0);
					g_Enemy3[i].watch = true;
				}

				WatchEnemy3(i);

			}
			// 見つけていない
			else
			{
				if (g_Enemy3[i].watch)
				{
					// 見失った時の処理（SE）
					PlaySound(g_watch_lost_SE3, 0);

					char work = rand() % ROOT_MAX;

					g_Enemy3[i].routenom = work;
					g_Enemy3[i].pos.x = SetRouteX(work) * CHIP_SIZE + (CHIP_SIZE / 2);
					g_Enemy3[i].pos.y = SetRouteY(work) * CHIP_SIZE + (CHIP_SIZE / 2);
				}

				g_Enemy3[i].watch = false;

				NoneWatchEnemy3(i);
			}
		}
	}
	// エネミー追加
	if (GetTimer() == 30)
	{
		SetEnemy3(1);
	}
	if (GetTimer() == 20)
	{
		SetEnemy3(2);
	}
	if (GetTimer() == 20)
	{
		SetEnemy3(3);
	}
	if (GetTimer() == 10)
	{
		SetEnemy3(4);
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy3(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy3[i].use == true)
		{
			PLAYER* player = GetPlayer();

			// 画面内に入っているか
			if (fabsf(g_Enemy3[i].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
				fabsf(g_Enemy3[i].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
			{
				//エネミーの位置やテクスチャー座標を反映
				float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Enemy3[i].pos.x - player->pos.x);	// エネミーの表示位置X
				float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Enemy3[i].pos.y - player->pos.y);	// エネミーの表示位置Y
				float pw = g_Enemy3[i].w;		// エネミーの表示幅
				float ph = g_Enemy3[i].h;		// エネミーの表示高さ
				D3DXCOLOR col;

				if (SerchPlayer3(GetPlayerPosition(), g_Enemy3[i].pos))
				{
					col = D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				DrawSpriteColor(g_EnemyTexture3, px, py, pw, ph,
					g_Enemy3[i].u, g_Enemy3[i].v,
					g_Enemy3[i].uh, g_Enemy3[i].vh,
					col);
			}
		}
	}
}

//=============================================================================
// 敵の発生処理
//=============================================================================
void SetEnemy3(int i)
{
	// もし未使用のデータを探す
	if (g_Enemy3[i].use == false)	// 未使用状態の敵データを見つける
	{
		g_Enemy3[i].use = true;		// 使用状態へ変更する

		// 出現したときのSE

		return;						// 敵をセットできたので終了する
	}
}

// 見つけたら
void WatchEnemy3(int i)
{
	// 旧版サーチ
	{
		//現在位置
		D3DXVECTOR2 position = g_Enemy3[i].pos;

		//目標地点
		D3DXVECTOR2 destination = GetPlayerPosition();

		//成分
		D3DXVECTOR2 components;

		//大きさ
		float magnitude;

		//方向（単位ベクトル）
		D3DXVECTOR2 direction;

		//成分計算
		components.x = destination.x - position.x;
		components.y = destination.y - position.y;

		//大きさ計算
		magnitude = (float)sqrt(components.x * components.x + components.y * components.y);

		//方向計算（正規化）
		direction.x = components.x / magnitude;
		direction.y = components.y / magnitude;

		// 横の移動量の方が大きいとき
		if (fabsf(direction.x) > fabsf(direction.y))
		{
			// 左に行くとき
			if (direction.x < 0)
			{
				g_Enemy3[i].u = 1.0f;
				g_Enemy3[i].v = 0.0f;
				g_Enemy3[i].uh = -0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
			else // 右に行くとき
			{
				g_Enemy3[i].u = 0.5f;
				g_Enemy3[i].v = 0.0f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
		}
		else // 縦の移動量の方が大きい or 同じとき
		{
			// 上に行くとき
			if (direction.y < 0)
			{
				g_Enemy3[i].u = 0.5f;
				g_Enemy3[i].v = 0.5f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
			else // 下に行くとき
			{
				g_Enemy3[i].u = 0.0f;
				g_Enemy3[i].v = 0.5f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
		}

		//移動後の位置を計算
		g_Enemy3[i].pos.x += direction.x * FIND_SPD;
		if (GetMapEnter3(D3DXVECTOR2(g_Enemy3[i].pos.x + direction.x * FIND_SPD, g_Enemy3[i].pos.y))
			== 1)
		{
			g_Enemy3[i].pos.x -= direction.x * FIND_SPD;
			g_Enemy3[i].notmove.x += fabsf(direction.x);

			if (!g_Enemy3[i].movecntX)
			{
				// 一定時間動けない（障害物に引っかかる）
				if (g_Enemy3[i].notmove.x > NONE_MOVE)
				{
					g_Enemy3[i].movecntX = true;
					g_Enemy3[i].notmove.x = 0.0f;
				}
			}
		}

		g_Enemy3[i].pos.y += direction.y * FIND_SPD;
		if (GetMapEnter3(D3DXVECTOR2(g_Enemy3[i].pos.x, g_Enemy3[i].pos.y + direction.y * FIND_SPD))
			== 1)
		{
			g_Enemy3[i].pos.y -= direction.y * FIND_SPD;
			g_Enemy3[i].notmove.y += fabsf(direction.y);

			if (!g_Enemy3[i].movecntY)
			{
				// 一定時間動けない（障害物に引っかかる）
				if (g_Enemy3[i].notmove.y > NONE_MOVE)
				{
					g_Enemy3[i].movecntY = true;
					g_Enemy3[i].notmove.y = 0.0f;
				}
			}

		}

		// 一定時間動けない（障害物に引っかかる）
		if (g_Enemy3[i].movecntX)
		{
			g_Enemy3[i].movecntX = false;

			// 見失った時の処理（SE）
			PlaySound(g_watch_lost_SE3, 0);

			char work = rand() % ROOT_MAX;

			g_Enemy3[i].routenom = work;
			g_Enemy3[i].pos.x = SetRoute3X_1(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_1(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_2(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_2(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_3(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_3(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_4(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_4(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_5(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_5(work) * CHIP_SIZE + (CHIP_SIZE / 2);

		}
		if (g_Enemy3[i].movecntY)
		{
			g_Enemy3[i].movecntY = false;

			// 見失った時の処理（SE）
			PlaySound(g_watch_lost_SE3, 0);

			char work = rand() % ROOT_MAX;

			g_Enemy3[i].routenom = work;
			g_Enemy3[i].pos.x = SetRoute3X_1(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_1(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_2(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_2(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_3(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_3(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_4(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_4(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.x = SetRoute3X_5(work) * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = SetRoute3Y_5(work) * CHIP_SIZE + (CHIP_SIZE / 2);
		}

	}

}

// 見つけていなかったら
void NoneWatchEnemy3(int i)
{
	{
		//現在位置
		D3DXVECTOR2 position = g_Enemy3[i].pos;

		char work = g_Enemy3[i].routenom;

		if (g_Enemy3[i].pos.x < g_Route3X_1[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Enemy3[i].pos.x > g_Route3X_1[work] * CHIP_SIZE)
		{
			if (g_Enemy3[i].pos.y < g_Route3Y_1[work] * CHIP_SIZE + CHIP_SIZE &&
				g_Enemy3[i].pos.y > g_Route3Y_1[work] * CHIP_SIZE)
			{
				if (i % 2 == 0)
				{
					// 偶数 or 0
					work++;
					g_Enemy3[i].routenom++;
					if (work >= ROOT_MAX)
					{
						work = 0;
						g_Enemy3[i].routenom = 0;
					}
				}
				else
				{
					// 奇数
					work--;
					g_Enemy3[i].routenom--;
					if (work < 0)
					{
						work = ROOT_MAX;
						g_Enemy3[i].routenom = ROOT_MAX;
					}
				}


			}
		}
		
		if (g_Enemy3[i].pos.x < g_Route3X_2[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Enemy3[i].pos.x > g_Route3X_2[work] * CHIP_SIZE)
		{
			if (g_Enemy3[i].pos.y < g_Route3Y_2[work] * CHIP_SIZE + CHIP_SIZE &&
				g_Enemy3[i].pos.y > g_Route3Y_2[work] * CHIP_SIZE)
			{
				if (i % 2 == 0)
				{
					// 偶数 or 0
					work++;
					g_Enemy3[i].routenom++;
					if (work >= ROOT_MAX)
					{
						work = 0;
						g_Enemy3[i].routenom = 0;
					}
				}
				else
				{
					// 奇数
					work--;
					g_Enemy3[i].routenom--;
					if (work < 0)
					{
						work = ROOT_MAX;
						g_Enemy3[i].routenom = ROOT_MAX;
					}
				}


			}
		}
		
		if (g_Enemy3[i].pos.x < g_Route3X_3[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Enemy3[i].pos.x > g_Route3X_3[work] * CHIP_SIZE)
		{
			if (g_Enemy3[i].pos.y < g_Route3Y_3[work] * CHIP_SIZE + CHIP_SIZE &&
				g_Enemy3[i].pos.y > g_Route3Y_3[work] * CHIP_SIZE)
			{
				if (i % 2 == 0)
				{
					// 偶数 or 0
					work++;
					g_Enemy3[i].routenom++;
					if (work >= ROOT_MAX)
					{
						work = 0;
						g_Enemy3[i].routenom = 0;
					}
				}
				else
				{
					// 奇数
					work--;
					g_Enemy3[i].routenom--;
					if (work < 0)
					{
						work = ROOT_MAX;
						g_Enemy3[i].routenom = ROOT_MAX;
					}
				}


			}
		}
		
		if (g_Enemy3[i].pos.x < g_Route3X_4[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Enemy3[i].pos.x > g_Route3X_4[work] * CHIP_SIZE)
		{
			if (g_Enemy3[i].pos.y < g_Route3Y_4[work] * CHIP_SIZE + CHIP_SIZE &&
				g_Enemy3[i].pos.y > g_Route3Y_4[work] * CHIP_SIZE)
			{
				if (i % 2 == 0)
				{
					// 偶数 or 0
					work++;
					g_Enemy3[i].routenom++;
					if (work >= ROOT_MAX)
					{
						work = 0;
						g_Enemy3[i].routenom = 0;
					}
				}
				else
				{
					// 奇数
					work--;
					g_Enemy3[i].routenom--;
					if (work < 0)
					{
						work = ROOT_MAX;
						g_Enemy3[i].routenom = ROOT_MAX;
					}
				}


			}
		}
		
		if (g_Enemy3[i].pos.x < g_Route3X_5[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Enemy3[i].pos.x > g_Route3X_5[work] * CHIP_SIZE)
		{
			if (g_Enemy3[i].pos.y < g_Route3Y_5[work] * CHIP_SIZE + CHIP_SIZE &&
				g_Enemy3[i].pos.y > g_Route3Y_5[work] * CHIP_SIZE)
			{
				if (i % 2 == 0)
				{
					// 偶数 or 0
					work++;
					g_Enemy3[i].routenom++;
					if (work >= ROOT_MAX)
					{
						work = 0;
						g_Enemy3[i].routenom = 0;
					}
				}
				else
				{
					// 奇数
					work--;
					g_Enemy3[i].routenom--;
					if (work < 0)
					{
						work = ROOT_MAX;
						g_Enemy3[i].routenom = ROOT_MAX;
					}
				}


			}
		}

		//目標地点
		D3DXVECTOR2 destination = D3DXVECTOR2(g_Route3X_1[work] * CHIP_SIZE + (CHIP_SIZE / 2),
			g_Route3Y_1[work] * CHIP_SIZE + (CHIP_SIZE / 2));
		if (i % 4 == 0)
		{
			// １体目
			g_Enemy3[i].pos.x = g_Route3X_1[work] * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = g_Route3Y_1[work] * CHIP_SIZE + (CHIP_SIZE / 2);
		}
		else if (i % 4 == 1)
		{
			// ２体目
			g_Enemy3[i].pos.x = g_Route3X_2[work] * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = g_Route3Y_2[work] * CHIP_SIZE + (CHIP_SIZE / 2);
		}
		else if (i % 4 == 2)
		{
			// ３体目
			g_Enemy3[i].pos.x = g_Route3X_3[work] * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = g_Route3Y_3[work] * CHIP_SIZE + (CHIP_SIZE / 2);
		}
		else if (i % 4 == 3)
		{
			// ４体目
			g_Enemy3[i].pos.x = g_Route3X_4[work] * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = g_Route3Y_4[work] * CHIP_SIZE + (CHIP_SIZE / 2);
		}
		else if (i % 4 == 4)
		{
			// 5体目
			g_Enemy3[i].pos.x = g_Route3X_5[work] * CHIP_SIZE + (CHIP_SIZE / 2);
			g_Enemy3[i].pos.y = g_Route3Y_5[work] * CHIP_SIZE + (CHIP_SIZE / 2);
		}
		//成分
		D3DXVECTOR2 components;

		//大きさ
		float magnitude;

		//方向（単位ベクトル）
		D3DXVECTOR2 direction;

		//成分計算
		components.x = destination.x - position.x;
		components.y = destination.y - position.y;

		//大きさ計算
		magnitude = (float)sqrt(components.x * components.x + components.y * components.y);

		//方向計算（正規化）
		direction.x = components.x / magnitude;
		direction.y = components.y / magnitude;

		// 横の移動量の方が大きいとき
		if (fabsf(direction.x) > fabsf(direction.y))
		{
			// 左に行くとき
			if (direction.x < 0)
			{
				g_Enemy3[i].u = 1.0f;
				g_Enemy3[i].v = 0.0f;
				g_Enemy3[i].uh = -0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
			else // 右に行くとき
			{
				g_Enemy3[i].u = 0.5f;
				g_Enemy3[i].v = 0.0f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
		}
		else // 縦の移動量の方が大きい or 同じとき
		{
			// 上に行くとき
			if (direction.y < 0)
			{
				g_Enemy3[i].u = 0.5f;
				g_Enemy3[i].v = 0.5f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
			else // 下に行くとき
			{
				g_Enemy3[i].u = 0.0f;
				g_Enemy3[i].v = 0.5f;
				g_Enemy3[i].uh = 0.5f;
				g_Enemy3[i].vh = 0.5f;
			}
		}

		//移動後の位置を計算
		g_Enemy3[i].pos.x += direction.x * ENEMY_SPD;
		g_Enemy3[i].pos.y += direction.y * ENEMY_SPD;

	}
}

// 範囲内にプレイヤーが入り込んだら
bool SerchPlayer3(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos)
{
	D3DXVECTOR2 maxRange, minRange;

	minRange.x = Enemypos.x - SERCH_RANGE;
	minRange.y = Enemypos.y - SERCH_RANGE;
	maxRange.x = Enemypos.x + SERCH_RANGE;
	maxRange.y = Enemypos.y + SERCH_RANGE;

	//X軸の判定
	if (minRange.x < Playerpos.x &&
		maxRange.x > Playerpos.x)
	{
		//Y軸の判定
		if (minRange.y < Playerpos.y &&
			maxRange.y > Playerpos.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}


//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
ENEMY* GetEnemy3(void)
{
	return &g_Enemy3[0];
}