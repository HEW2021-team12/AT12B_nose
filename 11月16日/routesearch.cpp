//=============================================================================
//
// �T������ [routesearch.cpp]
// Author : �Îs
//
//=============================================================================
#include "enemy.h"
#include "routesearch.h"
#include "bg.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNT_RIMIT         (MAP_SIZE_X * MAP_SIZE_X)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//player�̈ʒu�ɍŒZ�o�H�ňړ�����
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

    // A*�T����
    // �I�[�v�����X�g�ɊJ�n�m�[�h��ǉ�
    OpenList[y][x] = true;
    while (!Finish && n < 100)
    {
        bool loopcansel = false;
        int work = 100;
        n++;

        // ���݂̃m�[�h���I�[�v�����X�g�̍ł��X�R�A�̏������m�[�h
        // �������鎞�͔ԍ����Ⴂ���̂���
        {// �ŏ��̃X�R�A��T��
            for (int dy = 0; dy < MAP_SIZE_Y; dy++)
            {
                for (int dx = 0; dx < MAP_SIZE_X; dx++)
                {
                    //�I�[�v�����X�g�ɂ���A�N���[�Y�ɂȂ��A���O�̃X�R�A��菬�����Ƃ�
                    if (OpenList[dy][dx] &&
                        !CloseList[dy][dx] &&
                        map_score[dy][dx] < work)
                    {
                        work = map_score[dy][dx];
                    }
                }
            }

            // �������̃X�R�A�ɊY��������W�����݃m�[�h�ɐݒ�
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

        // ���݃m�[�h���^�[�Q�b�g�m�[�h�̂Ƃ�
        if (myY == targetY && myX == targetX)
        {
            // �o�H�̊���
            Finish = true;

            // �^�[�Q�b�g�̃m�[�h�������N���X�g�ɍڂ�̂ő��v�Ȃ͂�
        }
        else
        {
            // ���݂̃m�[�h���N���[�Y�h���X�g�Ɉڂ�
            CloseList[myY][myX] = true;

            // ���݂̃m�[�h�ɗאڂ���e�m�[�h�𒲂ׁA�X�R�A�v�Z
            {
                // �����
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
            
                // ������
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

                // ������
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

                // �E����
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

    // �����N�̗����H��
    myX = LinkList[targetY][targetX] % 100; // �]��
    myY = LinkList[targetY][targetX] / 100; // ��
    targetX = myX;
    targetY = myY;
    Finish = false;
    n = 0;

    // �����̂����Ŗ����ɉ���Ă�
    // �܂胊���N�����������H
    while (!Finish && n < 100)
    {
        // �P�}�X�ȓ��ɃG�l�~�[�̍��W����������
        {
            // ���ݒl�̏オ�X�^�[�g�Ȃ�
            if (myX == x && myY - 1 == y)
            {
                Finish = true;
                return MOVE_UP;
            }
            // ���ݒl�̉����X�^�[�g�Ȃ�
            if (myX == x && myY + 1 == y)
            {
                Finish = true;
                return MOVE_DOWN;
            }
            // ���ݒl�̍����X�^�[�g�Ȃ�
            if (myX - 1 == x && myY == y)
            {
                Finish = true;
                return MOVE_LEFT;
            }
            // ���ݒl�̏オ�X�^�[�g�Ȃ�
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

    // �����ɂ����Ƃ������Ƃ͐���ɓ����Ă��Ȃ�
    return MOVE_NONE;
}