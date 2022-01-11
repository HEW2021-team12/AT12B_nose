/*==============================================================================

   レーザー [razer.cpp]
	Author :	古市
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "texture.h"
#include "player.h"
#include "sprite.h"
#include "main.h"
#include "map.h"
#include <time.h>
#include "sound.h"
#include "timer.h"
#include "razer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define RAZER_SIZEX			(200.0f)
#define RAZER_SIZEY			(100.0f)

// サイズを設置場所で変更したいならここで宣言してちゃんと初期化すること


#define RAZER_COUNT			(250)		// useがfalseになり続けるカウント
#define RAZER_KEEP			(400)		// useがtrueになり続けるカウント

#define RAZER_POS_X1		(28)
#define RAZER_POS_Y1		(5)

#define RAZER_POS_X2		(3)
#define RAZER_POS_Y2		(17)

#define RAZER_POS_X3		(25)
#define RAZER_POS_Y3		(24)

#define RAZER_POS_X4		(29)
#define RAZER_POS_Y4		(25)

#define RAZER_POS_X5		(26)
#define RAZER_POS_Y5		(28)

#define RAZER_POS_X6		(25)
#define RAZER_POS_Y6		(18)

#define RAZER_POS_X7		(12)
#define RAZER_POS_Y7		(10)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

unsigned char	g_RazerTexture3 = 0;

// メモリ確保用アドレス
RAZER* g_Razer3;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRazer3(void)
{
	g_RazerTexture3 = LoadTexture("data/TEXTURE/razer.png");

	// メモリ確保
	g_Razer3 = new RAZER[RAZER3_MAX];

	// レーザー構造体の初期化
	for (int i = 0; i < RAZER3_MAX; i++)
	{
		g_Razer3[i].use = false;
		g_Razer3[i].w = RAZER_SIZEX;
		g_Razer3[i].h = RAZER_SIZEY;

		g_Razer3[i].u = 0.0f;
		g_Razer3[i].v = 0.0f;
		g_Razer3[i].uh = RAZER_U;
		g_Razer3[i].vh = RAZER_V;

		g_Razer3[i].setcount = 0;

		// 一つ目
		if (i == 0)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X1;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y1;
		}
		// 二つ目
		if (i == 1)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X2;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y2;
		}
		// 三つ目
		if (i == 2)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X3;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y3;
		}
		// 四つ目
		if (i == 3)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X4;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y4;
		}
		// 五つ目
		if (i == 4)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X5;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y5;
		}
		// 六つ目
		if (i == 5)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X6;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y6;
		}
		// 七つ目
		if (i == 6)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X7;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y7;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRazer3(void)
{
	// メモリ解放
	delete[] g_Razer3;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRazer3(void)
{
	for (int i = 0; i < RAZER3_MAX; i++)
	{
		if (g_Razer3[i].use)
		{
			g_Razer3[i].setcount++;

			if (g_Razer3[i].setcount > RAZER_KEEP)
			{
				g_Razer3[i].use = false;
				g_Razer3[i].setcount = 0;
			}
		}
		else
		{
			g_Razer3[i].setcount++;

			if (g_Razer3[i].setcount > RAZER_COUNT)
			{
				g_Razer3[i].changecount = g_Razer3[i].setcount - RAZER_COUNT;

				g_Razer3[i].u = g_Razer3[i].changecount * RAZER_U;

				if (g_Razer3[i].changecount >= RAZER_NUM)
				{
					g_Razer3[i].changecount = 0;
					g_Razer3[i].setcount = 0;
					g_Razer3[i].use = true;
				}
			}
			else
			{
				g_Razer3[i].u = 0.0f;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRazer3(void)
{

	PLAYER* player = GetPlayer();

	for (int i = 0; i < RAZER3_MAX; i++)
	{
		// 画面内に入っているか
		if (fabsf(g_Razer3[i].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
			fabsf(g_Razer3[i].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
		{

			//エネミーの位置やテクスチャー座標を反映
			float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Razer3[i].pos.x - player->pos.x);	// エネミーの表示位置X
			float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Razer3[i].pos.y - player->pos.y);	// エネミーの表示位置Y
			float pw = g_Razer3[i].w;		// エネミーの表示幅
			float ph = g_Razer3[i].h;		// エネミーの表示高さ
			D3DXCOLOR col;

			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_Razer3[i].use)
			{
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				DrawSpriteColor(g_RazerTexture3, px, py, pw, ph,
					RAZER_U * (RAZER_NUM - 1), g_Razer3[i].v,
					g_Razer3[i].uh, g_Razer3[i].vh,
					col);
			}
			else
			{
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				DrawSpriteColor(g_RazerTexture3, px, py, pw, ph,
					g_Razer3[i].u, g_Razer3[i].v,
					g_Razer3[i].uh, g_Razer3[i].vh,
					col);
			}
		}
	}
}

//=============================================================================
// レーザー構造体の先頭アドレスを取得
//=============================================================================
RAZER* GetRazer3(void)
{
	return g_Razer3;
}