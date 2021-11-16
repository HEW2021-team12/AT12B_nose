//=============================================================================
//
// 探索処理 [routesearch.cpp]
// Author : 古市
//
//=============================================================================
#include "enemy.h"
#include "routesearch.h"
#include "bg.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COUNT_RIMIT         (MAP_SIZE_X * MAP_SIZE_X)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//playerの位置に最短経路で移動する
MOVE_STATE moveEnemy(int x, int y, int targetX, int targetY)
{
    int map[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };
    int map_score[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };

    for (int dy = 0; dy < MAP_SIZE_Y; dy++)
    {
        for (int dx = 0; dx < MAP_SIZE_X; dx++)
        {
            map[dy][dx] = GetMap(dx, dy);
        }
    }

    int LinkList[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };
    bool OpenList[MAP_SIZE_Y][MAP_SIZE_X] = { false };
    bool CloseList[MAP_SIZE_Y][MAP_SIZE_X] = { false };
    bool Finish = false;

    int n = 0;
    int myX = x;
    int myY = y;

    // A*探索部
    // オープンリストに開始ノードを追加
    OpenList[y][x] = true;
    while (!Finish && n < 100)
    {
        bool loopcansel = false;
        int work = 100;
        n++;

        // 現在のノード＝オープンリストの最もスコアの小さいノード
        // 複数ある時は番号が若いものが先
        {// 最小のスコアを探す
            for (int dy = 0; dy < MAP_SIZE_Y; dy++)
            {
                for (int dx = 0; dx < MAP_SIZE_X; dx++)
                {
                    //オープンリストにあり、クローズにない、かつ前のスコアより小さいとき
                    if (OpenList[dy][dx] &&
                        !CloseList[dy][dx] &&
                        map_score[dy][dx] < work)
                    {
                        work = map_score[dy][dx];
                    }
                }
            }

            // さっきのスコアに該当する座標を現在ノードに設定
            for (int dy = 0; dy < MAP_SIZE_Y; dy++)
            {
                for (int dx = 0; dx < MAP_SIZE_X; dx++)
                {
                    if (OpenList[dy][dx] &&
                        !CloseList[dy][dx] &&
                        work == map_score[dy][dx])
                    {
                        myX = dx;
                        myY = dy;
                    }
                }
            }
        }

        // 現在ノードがターゲットノードのとき
        if (myY == targetY && myX == targetX)
        {
            // 経路の完成
            Finish = true;

            // ターゲットのノードもリンクリストに載るので大丈夫なはず
        }
        else
        {
            // 現在のノードをクローズドリストに移す
            CloseList[myY][myX] = true;

            // 現在のノードに隣接する各ノードを調べ、スコア計算
            {
                // 上方向
                if (!OpenList[myY - 1][myX] &&
                    !CloseList[myY - 1][myX] &&
                    map[myY - 1][myX] != 1)
                {
                    OpenList[myY - 1][myX] = true;
                    map_score[myY - 1][myX] += abs((myY - 1) - y);
                    map_score[myY - 1][myX] += abs((myX) - x);

                    map_score[myY - 1][myX] += abs((myY - 1) - targetY);
                    map_score[myY - 1][myX] += abs((myX) - targetX);

                    LinkList[myY - 1][myX] = (myY * 100) + myX;
                }
            
                // 下方向
                if (!OpenList[myY + 1][myX] &&
                    !CloseList[myY + 1][myX] &&
                    map[myY + 1][myX] != 1)
                {
                    OpenList[myY + 1][myX] = true;
                    map_score[myY + 1][myX] += abs((myY + 1) - y);
                    map_score[myY + 1][myX] += abs((myX) - x);

                    map_score[myY + 1][myX] += abs((myY + 1) - targetY);
                    map_score[myY + 1][myX] += abs((myX) - targetX);

                    LinkList[myY + 1][myX] = (myY * 100) + myX;
                }

                // 左方向
                if (!OpenList[myY][myX - 1] &&
                    !CloseList[myY][myX - 1] &&
                    map[myY][myX - 1] != 1)
                {
                    OpenList[myY][myX - 1] = true;
                    map_score[myY][myX - 1] += abs((myY) - y);
                    map_score[myY][myX - 1] += abs((myX - 1) - x);

                    map_score[myY][myX - 1] += abs((myY) - targetY);
                    map_score[myY][myX - 1] += abs((myX - 1) - targetX);

                    LinkList[myY][myX - 1] = (myY * 100) + myX;
                }

                // 右方向
                if (!OpenList[myY][myX + 1] &&
                    !CloseList[myY][myX + 1] &&
                    map[myY][myX + 1] != 1)
                {
                    OpenList[myY][myX + 1] = true;
                    map_score[myY][myX + 1] += abs((myY) - y);
                    map_score[myY][myX + 1] += abs((myX + 1) - x);

                    map_score[myY][myX + 1] += abs((myY) - targetY);
                    map_score[myY][myX + 1] += abs((myX + 1) - targetX);

                    LinkList[myY][myX + 1] = (myY * 100) + myX;
                }
            }
        }
    }

    // リンクの流れを辿る
    myX = LinkList[targetY][targetX] % 100; // 余り
    myY = LinkList[targetY][targetX] / 100; // 商
    targetX = myX;
    targetY = myY;
    Finish = false;
    n = 0;

    // ここのせいで無限に回ってる
    // つまりリンクがおかしい？
    while (!Finish && n < 100)
    {
        // １マス以内にエネミーの座標があったら
        {
            // 現在値の上がスタートなら
            if (myX == x && myY - 1 == y)
            {
                Finish = true;
                return MOVE_UP;
            }
            // 現在値の下がスタートなら
            if (myX == x && myY + 1 == y)
            {
                Finish = true;
                return MOVE_DOWN;
            }
            // 現在値の左がスタートなら
            if (myX - 1 == x && myY == y)
            {
                Finish = true;
                return MOVE_LEFT;
            }
            // 現在値の上がスタートなら
            if (myX + 1 == x && myY == y)
            {
                Finish = true;
                return MOVE_RIGHT;
            }
        }
        
        myX = LinkList[targetY][targetX] % 100;
        myY = LinkList[targetY][targetX] / 100;
        targetX = myX;
        targetY = myY;

        n++;
    }

    // ここにきたということは正常に動いていない
    return MOVE_NONE;
}