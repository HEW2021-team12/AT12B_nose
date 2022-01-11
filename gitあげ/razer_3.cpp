/*==============================================================================

   ���[�U�[ [razer.cpp]
	Author :	�Îs
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
// �}�N����`
//*****************************************************************************

#define RAZER_SIZEX			(200.0f)
#define RAZER_SIZEY			(100.0f)

// �T�C�Y��ݒu�ꏊ�ŕύX�������Ȃ炱���Ő錾���Ă����Ə��������邱��


#define RAZER_COUNT			(250)		// use��false�ɂȂ葱����J�E���g
#define RAZER_KEEP			(400)		// use��true�ɂȂ葱����J�E���g

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
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

unsigned char	g_RazerTexture3 = 0;

// �������m�ۗp�A�h���X
RAZER* g_Razer3;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRazer3(void)
{
	g_RazerTexture3 = LoadTexture("data/TEXTURE/razer.png");

	// �������m��
	g_Razer3 = new RAZER[RAZER3_MAX];

	// ���[�U�[�\���̂̏�����
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

		// ���
		if (i == 0)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X1;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y1;
		}
		// ���
		if (i == 1)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X2;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y2;
		}
		// �O��
		if (i == 2)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X3;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y3;
		}
		// �l��
		if (i == 3)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X4;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y4;
		}
		// �܂�
		if (i == 4)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X5;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y5;
		}
		// �Z��
		if (i == 5)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X6;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y6;
		}
		// ����
		if (i == 6)
		{
			g_Razer3[i].pos.x = CHIP_SIZE * RAZER_POS_X7;
			g_Razer3[i].pos.y = CHIP_SIZE * RAZER_POS_Y7;
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRazer3(void)
{
	// ���������
	delete[] g_Razer3;
}

//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void DrawRazer3(void)
{

	PLAYER* player = GetPlayer();

	for (int i = 0; i < RAZER3_MAX; i++)
	{
		// ��ʓ��ɓ����Ă��邩
		if (fabsf(g_Razer3[i].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
			fabsf(g_Razer3[i].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
		{

			//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Razer3[i].pos.x - player->pos.x);	// �G�l�~�[�̕\���ʒuX
			float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Razer3[i].pos.y - player->pos.y);	// �G�l�~�[�̕\���ʒuY
			float pw = g_Razer3[i].w;		// �G�l�~�[�̕\����
			float ph = g_Razer3[i].h;		// �G�l�~�[�̕\������
			D3DXCOLOR col;

			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_Razer3[i].use)
			{
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				DrawSpriteColor(g_RazerTexture3, px, py, pw, ph,
					RAZER_U * (RAZER_NUM - 1), g_Razer3[i].v,
					g_Razer3[i].uh, g_Razer3[i].vh,
					col);
			}
			else
			{
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				DrawSpriteColor(g_RazerTexture3, px, py, pw, ph,
					g_Razer3[i].u, g_Razer3[i].v,
					g_Razer3[i].uh, g_Razer3[i].vh,
					col);
			}
		}
	}
}

//=============================================================================
// ���[�U�[�\���̂̐擪�A�h���X���擾
//=============================================================================
RAZER* GetRazer3(void)
{
	return g_Razer3;
}