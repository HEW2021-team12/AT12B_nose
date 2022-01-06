//=============================================================================
//
// スライム処理 [slime.cpp]
// Author : 古市
//
//=============================================================================
#include "slime.h"
#include "texture.h"
#include "player.h"
#include "sprite.h"
#include "main.h"
#include "map.h"
#include <time.h>
#include "sound.h"
#include "timer.h"
#include "patrol.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define SLIME_SPD			(1.1f)
#define SLIME_SIZE			(50.0f)

#define BABBLE_SIZE			(40.0f)
#define BABBLE_COUNT		(300)

#define SET_SPD				(150)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void SetBabble3(int i, D3DXVECTOR2 pos);
void MoveSlime3(int i);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
unsigned char	g_SlimeTexture3 = 0;
unsigned char	g_BabbleTexture3 = 0;
//unsigned char	g_Slime_SE = 0;

// メモリ確保用アドレス
SLIME* g_Slime3;			  // スライム構造体
BABBLE** g_Babble3;			  // バブル構造体
char* g_RouteSlimeX3;		  // 巡回ルート用
char* g_RouteSlimeY3;		  // 巡回ルート用

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSlime3(void)
{
	g_SlimeTexture3 = LoadTexture("data/TEXTURE/slime.png");
	g_BabbleTexture3 = LoadTexture("data/TEXTURE/tako.png");

	// メモリ確保
	g_Slime3 = new SLIME[SLIME_MAX];
	g_Babble3 = new BABBLE * [SLIME_MAX];

	for (int i = 0; i < SLIME_MAX; i++)
	{
		g_Babble3[i] = new BABBLE[BABBLE_MAX];
	}

	g_RouteSlimeX3 = new char[ROOT_MAX];
	g_RouteSlimeY3 = new char[ROOT_MAX];

	// スライム構造体の初期化
	for (int i = 0; i < SLIME_MAX; i++)
	{
		// １体目
		if (i == 0)
		{
			g_Slime3[i].use = true;
			g_Slime3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 5;
			g_Slime3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 5;
			g_Slime3[i].routenom = 5;
		}

		// 共通
		g_Slime3[i].h = SLIME_SIZE;
		g_Slime3[i].w = SLIME_SIZE;
		g_Slime3[i].vel = D3DXVECTOR2(SLIME_SPD, SLIME_SPD);

		// スライムUV
		g_Slime3[i].u = 0.0f;
		g_Slime3[i].v = 0.0f;
		g_Slime3[i].uh = 1.0f;
		g_Slime3[i].vh = 1.0f;
	}

	// 巡回ルート設定
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_RouteSlimeX3[r] = SetRouteX(r);
		g_RouteSlimeY3[r] = SetRouteY(r);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSlime3(void)
{
	// メモリ解放
	delete[] g_Slime3;
	delete[] g_Babble3;
	delete[] g_RouteSlimeX3;
	delete[] g_RouteSlimeY3;
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateSlime3(void)
{
	for (int i = 0; i < SLIME_MAX; i++)
	{
		if (g_Slime3[i].use)
		{
			MoveSlime3(i);

			if (g_Slime3[i].setcount > SET_SPD)
			{
				g_Slime3[i].setcount = 0;
				SetBabble3(i, g_Slime3[i].pos);
			}
			else
			{
				g_Slime3[i].setcount++;
			}
		}

		for (int j = 0; j < BABBLE_MAX; j++)
		{
			if (g_Babble3[i][j].use)
			{
				g_Babble3[i][j].count--;

				if (g_Babble3[i][j].count < 0)
				{
					g_Babble3[i][j].use = false;
				}
			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawSlime3(void)
{
	// スライム
	for (int i = 0; i < SLIME_MAX; i++)
	{
		// バブル
		for (int j = 0; j < BABBLE_MAX; j++)
		{
			if (g_Babble3[i][j].use)
			{
				PLAYER* player = GetPlayer();

				// 画面内に入っているか
				if (fabsf(g_Babble3[i][j].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
					fabsf(g_Babble3[i][j].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
				{
					//エネミーの位置やテクスチャー座標を反映
					float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Babble3[i][j].pos.x - player->pos.x);	// エネミーの表示位置X
					float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Babble3[i][j].pos.y - player->pos.y);	// エネミーの表示位置Y
					float pw = g_Babble3[i][j].w;		// エネミーの表示幅
					float ph = g_Babble3[i][j].h;		// エネミーの表示高さ
					D3DXCOLOR col;

					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// １枚のポリゴンの頂点とテクスチャ座標を設定
					DrawSpriteColor(g_BabbleTexture3, px, py, pw, ph,
						g_Babble3[i][j].u, g_Babble3[i][j].v,
						g_Babble3[i][j].uh, g_Babble3[i][j].vh,
						col);
				}
			}
		}

		// スライム
		if (g_Slime3[i].use)
		{
			PLAYER* player = GetPlayer();

			// 画面内に入っているか
			if (fabsf(g_Slime3[i].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
				fabsf(g_Slime3[i].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
			{
				//エネミーの位置やテクスチャー座標を反映
				float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Slime3[i].pos.x - player->pos.x);	// エネミーの表示位置X
				float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Slime3[i].pos.y - player->pos.y);	// エネミーの表示位置Y
				float pw = g_Slime3[i].w;		// エネミーの表示幅
				float ph = g_Slime3[i].h;		// エネミーの表示高さ
				D3DXCOLOR col;

				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// １枚のポリゴンの頂点とテクスチャ座標を設定
				DrawSpriteColor(g_SlimeTexture3, px, py, pw, ph,
					g_Slime3[i].u, g_Slime3[i].v,
					g_Slime3[i].uh, g_Slime3[i].vh,
					col);
			}
		}
	}
}

//=============================================================================
// スライム構造体の先頭アドレスを取得
//=============================================================================
SLIME* GetSlime3(void)
{
	return g_Slime3;
}

BABBLE** GetBabble3(void)
{
	return g_Babble3;
}

// バブルを発生させる
void SetBabble3(int i, D3DXVECTOR2 pos)
{
	for (int j = 0; j < BABBLE_MAX; j++)
	{
		// もし未使用のデータを探す
		if (g_Babble3[i][j].use == false)	// 未使用状態の敵データを見つける
		{
			g_Babble3[i][j].use = true;		// 使用状態へ変更する
			g_Babble3[i][j].pos = pos;
			g_Babble3[i][j].w = BABBLE_SIZE;
			g_Babble3[i][j].h = BABBLE_SIZE;

			g_Babble3[i][j].count = BABBLE_COUNT;

			g_Babble3[i][j].u = 0.0f;
			g_Babble3[i][j].v = 0.0f;
			g_Babble3[i][j].uh = 1.0f;
			g_Babble3[i][j].vh = 1.0f;

			// 出現したときのSE

			return;						// 敵をセットできたので終了する
		}
	}
}

// スライムの移動
void MoveSlime3(int i)
{
	//現在位置
	D3DXVECTOR2 position = g_Slime3[i].pos;

	char work = g_Slime3[i].routenom;

	if (g_Slime3[i].pos.x < g_RouteSlimeX3[work] * CHIP_SIZE + CHIP_SIZE &&
		g_Slime3[i].pos.x > g_RouteSlimeX3[work] * CHIP_SIZE)
	{
		if (g_Slime3[i].pos.y < g_RouteSlimeY3[work] * CHIP_SIZE + CHIP_SIZE &&
			g_Slime3[i].pos.y > g_RouteSlimeY3[work] * CHIP_SIZE)
		{
			if (i % 2 == 0)
			{
				// 偶数 or 0
				work++;
				g_Slime3[i].routenom++;
				if (work >= ROOT_MAX)
				{
					work = 0;
					g_Slime3[i].routenom = 0;
				}
			}
			else
			{
				// 奇数
				work--;
				g_Slime3[i].routenom--;
				if (work < 0)
				{
					work = ROOT_MAX;
					g_Slime3[i].routenom = ROOT_MAX;
				}
			}
		}
	}

	//目標地点
	D3DXVECTOR2 destination = D3DXVECTOR2(g_RouteSlimeX3[work] * CHIP_SIZE + (CHIP_SIZE / 2),
		g_RouteSlimeY3[work] * CHIP_SIZE + (CHIP_SIZE / 2));

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

	//移動後の位置を計算
	g_Slime3[i].pos.x += direction.x * g_Slime3[i].vel.x;
	g_Slime3[i].pos.y += direction.y * g_Slime3[i].vel.y;
}