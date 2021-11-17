//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "main.h"
#include "player.h"
#include "routesearch.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROT_SPD				(0.05f)
#define ENEMY_SPD			(2.0f)
#define ENEMY_SIZE			(55.0f)
#define MOVE_TIMER			(50)
#define SERCH_RANGE			(250.0f)
#define FIND_SPD			(2.0f)

#define SEARCH_TIMER		(CHIP_SIZE / ENEMY_SPD)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_EnemyTexture = 0;
static ENEMY g_Enemy;							  // エネミー構造体
static float MAPleft, MAPright, MAPtop, MAPunder; // エネミーの行動範囲
static int g_Enemy_Timer;
static int g_Search_Timer;
int move;
float g_U, g_V, g_Uh, g_Vh;
MOVE_STATE result;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	g_EnemyTexture = LoadTexture("data/TEXTURE/enemy.png");

	MAPleft = SCREEN_WIDTH / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_X / 2));
	MAPright = SCREEN_WIDTH / 2 - HALF_CHIP + CHIP_SIZE * ((MAP_SIZE_X / 2));

	MAPtop = SCREEN_HEIGHT / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_Y / 2));
	MAPunder = SCREEN_HEIGHT / 2 - HALF_CHIP + CHIP_SIZE * ((MAP_SIZE_Y / 2));

	// エネミー構造体の初期化
	g_Enemy.use   = true;
	g_Enemy.w     = ENEMY_SIZE;
	g_Enemy.h     = ENEMY_SIZE;
	g_Enemy.pos   = D3DXVECTOR2(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 150.0f);
	g_Enemy.rot   = 0.0f;
	g_Enemy.vel   = D3DXVECTOR2(ENEMY_SPD,ENEMY_SPD);

	g_Enemy_Timer = 0;
	g_Search_Timer = 0;

	// エネミーUV
	g_U = 0.0f;
	g_V = 0.0f;
	g_Uh = 0.0f;
	g_Vh = 0.0f;
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{

	if (g_Enemy.use == true)
	{
		// 追跡判定
		if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
		{// 見つけた(範囲内に入った)

			// エネミーがCHIP_SIZE分移動したら動作
			if (g_Search_Timer <= 0)
			{
				g_Search_Timer = (int)SEARCH_TIMER;

				// 新版サーチ
				{

					int Ex = 0, Ey = 0;
					int Px = 0, Py = 0;

					// エネミーのマップ座標特定
					{
						float sx, sy;

						// 横軸
						for (int x = 0; x < MAP_SIZE_X; x++)
						{
							sx = SCREEN_WIDTH / 2 + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);

							if (g_Enemy.pos.x < sx + CHIP_SIZE && // プレイヤー小、マップ大
								g_Enemy.pos.x > sx)				  // プレイヤー大、マップ小
							{

								if (x == 0)
								{
									Ex = 1;
								}
								else if (x == MAP_SIZE_X)
								{
									Ex = MAP_SIZE_X - 1;
								}
								else
								{
									Ex = x;
								}
							}
						}
						// 縦軸
						for (int y = 0; y < MAP_SIZE_Y; y++)
						{
							sy = SCREEN_HEIGHT / 2 + CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

							if (g_Enemy.pos.y < sy + CHIP_SIZE && // プレイヤー小、マップ大
								g_Enemy.pos.y > sy)				  // プレイヤー大、マップ小
							{
								if (y == 0)
								{
									Ey = 1;
								}
								else if (y == MAP_SIZE_Y)
								{
									Ey = MAP_SIZE_Y - 1;
								}
								else
								{
									Ey = y;
								}
							}
						}
					}

					// プレイヤーのマップ座標特定
					{
						D3DXVECTOR2 Ppos = GetPlayerPosition();

						float sx, sy;

						// 横軸
						for (int x = 0; x < MAP_SIZE_X; x++)
						{
							sx = SCREEN_WIDTH / 2 + (HALF_CHIP / 6 * 5) + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);

							if (Ppos.x < sx + CHIP_SIZE && // プレイヤー小、マップ大
								Ppos.x > sx)				  // プレイヤー大、マップ小
							{
								if (x == 0)
								{
									Px = 1;
								}
								else if (x == MAP_SIZE_X)
								{
									Px = MAP_SIZE_X - 1;
								}
								else
								{
									Px = x;
								}
							}
						}
						// 縦軸
						for (int y = 0; y < MAP_SIZE_Y; y++)
						{
							sy = SCREEN_HEIGHT / 2 + /*(HALF_CHIP / 3)*/ +CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

							if (Ppos.y < sy + CHIP_SIZE && // プレイヤー小、マップ大
								Ppos.y > sy)			   // プレイヤー大、マップ小
							{
								if (y == 0)
								{
									Py = 1;
								}
								else if (y == MAP_SIZE_Y)
								{
									Py = MAP_SIZE_Y - 1;
								}
								else
								{
									Py = y;
								}
							}
						}
					}

					// 新版サーチ
					// もしやこっちの引数がおかしいか？
					result = moveEnemy(1, 1, 5, 5);



					if (result == MOVE_UP)
					{
						g_Enemy.pos.y -= g_Enemy.vel.y;
						/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y - g_Enemy.vel.y),
							D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
							== 1)
						{
							g_Enemy.pos.y += g_Enemy.vel.y;
						}*/
						g_Search_Timer--;
					}
					if (result == MOVE_DOWN)
					{
						g_Enemy.pos.y += g_Enemy.vel.y;
						/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + g_Enemy.vel.y),
							D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
							== 1)
						{
							g_Enemy.pos.y -= g_Enemy.vel.y;
						}*/
						g_Search_Timer--;
					}
					if (result == MOVE_LEFT)
					{
						g_Enemy.pos.x -= g_Enemy.vel.x;
						/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x - g_Enemy.vel.x, g_Enemy.pos.y),
							D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
							== 1)
						{
							g_Enemy.pos.x += g_Enemy.vel.x;
						}*/

						g_Search_Timer--;
					}
					if (result == MOVE_RIGHT)
					{
						g_Enemy.pos.x += g_Enemy.vel.x;
						/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + g_Enemy.vel.x, g_Enemy.pos.y),
							D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
							== 1)
						{
							g_Enemy.pos.x -= g_Enemy.vel.x;
						}*/

						g_Search_Timer--;
					}
				}
			}

			// 旧版サーチ
			{
			//現在位置
			D3DXVECTOR2 position = g_Enemy.pos;

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
					g_U = 1.0f;
					g_V = 0.0f;
					g_Uh = -0.5f;
					g_Vh = 0.5f;
				}
				else // 右に行くとき
				{
					g_U = 0.5f;
					g_V = 0.0f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
			}
			else // 縦の移動量の方が大きい or 同じとき
			{
				// 上に行くとき
				if (direction.y < 0)
				{
					g_U = 0.5f;
					g_V = 0.5f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
				else // 下に行くとき
				{
					g_U = 0.0f;
					g_V = 0.5f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
			}

			//移動後の位置を計算
			g_Enemy.pos.x += direction.x * FIND_SPD;
			/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + direction.x * FIND_SPD, g_Enemy.pos.y),
				D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
				== 1)
			{
				g_Enemy.pos.x -= direction.x * FIND_SPD;
			}*/

			g_Enemy.pos.y += direction.y * FIND_SPD;
			/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + direction.y * FIND_SPD),
				D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
				== 1)
			{
				g_Enemy.pos.y -= direction.y * FIND_SPD;
			}*/

			}
			
		}
		// 見つけていない
		else 
		{
			g_Enemy_Timer++;

			if (g_Enemy_Timer > MOVE_TIMER)
			{
				move = rand() % 5;
				g_Enemy_Timer = 0;
				srand((unsigned)time(NULL));
			}

			// エネミー移動
			// 1:上　2:下　3:右　4:左　0:なし(待機)
			if (move == 1) // 上
			{
				g_Enemy.pos.y -= g_Enemy.vel.y;
				/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y - g_Enemy.vel.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.y += g_Enemy.vel.y;
				}*/
				g_U = 0.5f;
				g_V = 0.5f;
				g_Uh = 0.5f;
				g_Vh = 0.5f;
			}

			if (move == 2) // 下
			{
				g_Enemy.pos.y += g_Enemy.vel.y;
				/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + g_Enemy.vel.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.y -= g_Enemy.vel.y;
				}*/
				g_U = 0.0f;
				g_V = 0.5f;
				g_Uh = 0.5f;
				g_Vh = 0.5f;
			}

			if (move == 3) // 右
			{
				g_Enemy.pos.x += g_Enemy.vel.x;
				/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + g_Enemy.vel.x, g_Enemy.pos.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.x -= g_Enemy.vel.x;
				}*/
				g_U = 0.5f;
				g_V = 0.0f;
				g_Uh = 0.5f;
				g_Vh = 0.5f;
			}

			if (move == 4) // 左
			{
				g_Enemy.pos.x -= g_Enemy.vel.x;
				/*if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x - g_Enemy.vel.x, g_Enemy.pos.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.x += g_Enemy.vel.x;
				}*/
				g_U = 1.0f;
				g_V = 0.0f;
				g_Uh = -0.5f;
				g_Vh = 0.5f;
			}

			if (move == 0) // 待機
			{
				g_U = 0.0f;
				g_V = 0.0f;
				g_Uh = 0.5f;
				g_Vh = 0.5f;
			}

		}
		// 反射処理
		// 左端
		//if (g_Enemy.pos.x <= MAPleft)
		//{
		//	g_Enemy.pos.x = MAPleft;
		//}
		//// 右端
		//if (g_Enemy.pos.x >= MAPright)
		//{
		//	g_Enemy.pos.x = MAPright;
		//}
		//// 上端
		//if (g_Enemy.pos.y <= MAPtop)
		//{
		//	g_Enemy.pos.y = MAPtop;
		//}
		//// 下端
		//if (g_Enemy.pos.y >= MAPunder)
		//{
		//	g_Enemy.pos.y = MAPunder;
		//}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	if (g_Enemy.use == true)
	{
		//エネミーの位置やテクスチャー座標を反映
		float px = g_Enemy.pos.x;	// エネミーの表示位置X
		float py = g_Enemy.pos.y;	// エネミーの表示位置Y
		float pw = g_Enemy.w;		// エネミーの表示幅
		float ph = g_Enemy.h;		// エネミーの表示高さ
		D3DXCOLOR col;

		if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
		{
			col = D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		DrawSpriteColorRotate(g_EnemyTexture,px, py, pw, ph,
			g_U, g_V,
			g_Uh, g_Vh,
			col, g_Enemy.rot);
	}
}

//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy;
}


//=============================================================================
// 敵の発生処理
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos)
{
	// もし未使用のデータを探す
	if (g_Enemy.use == false)		// 未使用状態の敵データを見つける
	{
		g_Enemy.use = true;			// 使用状態へ変更する
		g_Enemy.pos = pos;			// 座標をセット
		g_Enemy.rot = 0.0f;			// 回転角のリセット
		return;						// 敵をセットできたので終了する
	}
	
}

bool SerchPlayer(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos)
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