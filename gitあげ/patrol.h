/*==============================================================================

   巡回ルート管理 [patrol.h]
	Author :	古市
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ステージ１
#define ROOT_MAX			(12)

// ステージ２
#define ROOT_MAX2			()

// ステージ３
#define ROOT_MAX3_1			(19)
#define ROOT_MAX3_2			(19)
#define ROOT_MAX3_3			(19)
#define ROOT_MAX3_4			(19)
#define ROOT_MAX3_5			(19)

// ステージ４
#define ROOT_MAX4			()

// ステージ５
#define ROOT_MAX5			()


// ステージ１
char SetRouteX(char number);
char SetRouteY(char number);

//// ステージ２
//char SetRouteX(char number);
//char SetRouteY(char number);
//
//// ステージ３
char SetRoute3X_1(char number);
char SetRoute3Y_1(char number);

char SetRoute3X_2(char number);
char SetRoute3Y_2(char number);

char SetRoute3X_3(char number);
char SetRoute3Y_3(char number);

char SetRoute3X_4(char number);
char SetRoute3Y_4(char number);

char SetRoute3X_5(char number);
char SetRoute3Y_5(char number);
//
//// ステージ４
//char SetRouteX(char number);
//char SetRouteY(char number);
//
//// ステージ５
//char SetRouteX(char number);
//char SetRouteY(char number);