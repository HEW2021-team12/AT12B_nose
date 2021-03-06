/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "fade.h"
#include "player.h"
#include "collision.h"
#include "enemy.h"
#include "map.h"
#include "sound.h"
#include "timer.h"
#include "slime.h"
#include "razer.h"
#include "warp.h"
#include "transparent_enemy.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
unsigned char g_BGMNo = 0;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	InitPlayer();
	InitEnemy();
	InitTransparent();
	InitSlime();
	InitRazer();
	InitWarp();
	InitMap();
	InitTimer();
	InitCollision();		// サウンド追加用

	g_BGMNo = LoadSound("data/BGM/BGM.wav");
	PlaySound(g_BGMNo, 255);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	StopSoundAll();

	//初期化とは逆順に終了処理を行う
	UninitMap();
	UninitPlayer();
	UninitTransparent();
	//UninitEnemy();
	UninitSlime();
	UninitWarp();
	UninitRazer();
	UninitTimer();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	UpdateMap();
	UpdateEnemy();
	UpdateTransparent();
	UpdateSlime();
	UpdateRazer();
	UpdateWarp();
	UpdatePlayer();
	
	UpdateCollision();
	UpdateTimer();

	//スペースキーが押されていて、フェード処理中ではないとき
	if (Keyboard_IsKeyDown(KK_ENTER) ||
		IsButtonTriggered(0, XINPUT_GAMEPAD_B)
		&& GetFadeState() == FADE_NONE)
	{
		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	DrawMap();
	DrawWarp();
	DrawPlayer();
	DrawEnemy();
	DrawTransparent();
	DrawSlime();
	DrawRazer();
	DrawTimer();
}