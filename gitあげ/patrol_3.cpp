/*==============================================================================

   巡回ルート管理 [patrol.cpp]
	Author :	古市
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "patrol.h"

// ルート座標値
const char g_Root3_1[2][ROOT_MAX3_1] =
{
	// 上がX 下がY
	{21,20,20,14,15,20,25,29,29,17,6 ,3 ,3 ,7 ,12,8 ,4 ,10,20 },
	{26,23,19,18,13,12,7 ,7 ,3 ,3 ,3 ,9 ,24,23,24,28,31,34,33 }
};

const char g_Root3_2[2][ROOT_MAX3_2] =
{
	// 上がX 下がY
	{15,20,25,29,29,17,6 ,3 ,3 ,7 ,12,8 ,4 ,10,20,21,20,20,14 },
	{13,12,7 ,7 ,3 ,3 ,3 ,9 ,24,23,24,28,31,34,33,26,23,19,18 }
};

const char g_Root3_3[2][ROOT_MAX3_3] =
{
	// 上がX 下がY
	{17,6 ,3 ,3 ,7 ,12,8 ,4 ,10,20,21,20,20,14,15,20,25,29,29 },
	{3 ,3 ,9 ,24,23,24,28,31,34,33,26,23,19,18,13,12,7 ,7 ,3  }
};

const char g_Root3_4[2][ROOT_MAX3_4] =
{
	// 上がX 下がY
	{7 ,12,8 ,4 ,10,20,21,20,20,14,15,20,25,29,29,17,6 ,3 ,3  },
	{23,24,28,31,34,33,26,23,19,18,13,12,7 ,7 ,3 ,3 ,3 ,9 ,24 }
};

const char g_Root3_5[2][ROOT_MAX3_5] =
{
	// 上がX 下がY
	{10,20,21,20,20,14,15,20,25,29,29,17,6 ,3 ,3 ,7 ,12,8 ,4  },
	{34,33,26,23,19,18,13,12,7 ,7 ,3 ,3 ,3 ,9 ,24,23,24,28,31 }
};

char SetRoute3X_1(char number)
{
	return g_Root3_1[0][number];
}

char SetRoute3Y_1(char number)
{
	return g_Root3_1[1][number];
}

char SetRoute3X_2(char number)
{
	return g_Root3_2[0][number];
}

char SetRoute3Y_2(char number)
{
	return g_Root3_2[1][number];
}

char SetRoute3X_3(char number)
{
	return g_Root3_3[0][number];
}

char SetRoute3Y_3(char number)
{
	return g_Root3_3[1][number];
}

char SetRoute3X_4(char number)
{
	return g_Root3_4[0][number];
}

char SetRoute3Y_4(char number)
{
	return g_Root3_4[1][number];
}

char SetRoute3X_5(char number)
{
	return g_Root3_5[0][number];
}

char SetRoute3Y_5(char number)
{
	return g_Root3_5[1][number];
}