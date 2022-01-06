//=============================================================================
//
// �X���C������ [slime.cpp]
// Author : �Îs
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
// �}�N����`
//*****************************************************************************

#define SLIME_SPD			(1.1f)
#define SLIME_SIZE			(50.0f)

#define BABBLE_SIZE			(40.0f)
#define BABBLE_COUNT		(300)

#define SET_SPD				(150)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void SetBabble3(int i, D3DXVECTOR2 pos);
void MoveSlime3(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
unsigned char	g_SlimeTexture3 = 0;
unsigned char	g_BabbleTexture3 = 0;
//unsigned char	g_Slime_SE = 0;

// �������m�ۗp�A�h���X
SLIME* g_Slime3;			  // �X���C���\����
BABBLE** g_Babble3;			  // �o�u���\����
char* g_RouteSlimeX3;		  // ���񃋁[�g�p
char* g_RouteSlimeY3;		  // ���񃋁[�g�p

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSlime3(void)
{
	g_SlimeTexture3 = LoadTexture("data/TEXTURE/slime.png");
	g_BabbleTexture3 = LoadTexture("data/TEXTURE/tako.png");

	// �������m��
	g_Slime3 = new SLIME[SLIME_MAX];
	g_Babble3 = new BABBLE * [SLIME_MAX];

	for (int i = 0; i < SLIME_MAX; i++)
	{
		g_Babble3[i] = new BABBLE[BABBLE_MAX];
	}

	g_RouteSlimeX3 = new char[ROOT_MAX];
	g_RouteSlimeY3 = new char[ROOT_MAX];

	// �X���C���\���̂̏�����
	for (int i = 0; i < SLIME_MAX; i++)
	{
		// �P�̖�
		if (i == 0)
		{
			g_Slime3[i].use = true;
			g_Slime3[i].pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * 5;
			g_Slime3[i].pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * 5;
			g_Slime3[i].routenom = 5;
		}

		// ����
		g_Slime3[i].h = SLIME_SIZE;
		g_Slime3[i].w = SLIME_SIZE;
		g_Slime3[i].vel = D3DXVECTOR2(SLIME_SPD, SLIME_SPD);

		// �X���C��UV
		g_Slime3[i].u = 0.0f;
		g_Slime3[i].v = 0.0f;
		g_Slime3[i].uh = 1.0f;
		g_Slime3[i].vh = 1.0f;
	}

	// ���񃋁[�g�ݒ�
	for (char r = 0; r < ROOT_MAX; r++)
	{
		g_RouteSlimeX3[r] = SetRouteX(r);
		g_RouteSlimeY3[r] = SetRouteY(r);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSlime3(void)
{
	// ���������
	delete[] g_Slime3;
	delete[] g_Babble3;
	delete[] g_RouteSlimeX3;
	delete[] g_RouteSlimeY3;
}
//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void DrawSlime3(void)
{
	// �X���C��
	for (int i = 0; i < SLIME_MAX; i++)
	{
		// �o�u��
		for (int j = 0; j < BABBLE_MAX; j++)
		{
			if (g_Babble3[i][j].use)
			{
				PLAYER* player = GetPlayer();

				// ��ʓ��ɓ����Ă��邩
				if (fabsf(g_Babble3[i][j].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
					fabsf(g_Babble3[i][j].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
				{
					//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
					float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Babble3[i][j].pos.x - player->pos.x);	// �G�l�~�[�̕\���ʒuX
					float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Babble3[i][j].pos.y - player->pos.y);	// �G�l�~�[�̕\���ʒuY
					float pw = g_Babble3[i][j].w;		// �G�l�~�[�̕\����
					float ph = g_Babble3[i][j].h;		// �G�l�~�[�̕\������
					D3DXCOLOR col;

					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
					DrawSpriteColor(g_BabbleTexture3, px, py, pw, ph,
						g_Babble3[i][j].u, g_Babble3[i][j].v,
						g_Babble3[i][j].uh, g_Babble3[i][j].vh,
						col);
				}
			}
		}

		// �X���C��
		if (g_Slime3[i].use)
		{
			PLAYER* player = GetPlayer();

			// ��ʓ��ɓ����Ă��邩
			if (fabsf(g_Slime3[i].pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
				fabsf(g_Slime3[i].pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
			{
				//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
				float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Slime3[i].pos.x - player->pos.x);	// �G�l�~�[�̕\���ʒuX
				float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Slime3[i].pos.y - player->pos.y);	// �G�l�~�[�̕\���ʒuY
				float pw = g_Slime3[i].w;		// �G�l�~�[�̕\����
				float ph = g_Slime3[i].h;		// �G�l�~�[�̕\������
				D3DXCOLOR col;

				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				DrawSpriteColor(g_SlimeTexture3, px, py, pw, ph,
					g_Slime3[i].u, g_Slime3[i].v,
					g_Slime3[i].uh, g_Slime3[i].vh,
					col);
			}
		}
	}
}

//=============================================================================
// �X���C���\���̂̐擪�A�h���X���擾
//=============================================================================
SLIME* GetSlime3(void)
{
	return g_Slime3;
}

BABBLE** GetBabble3(void)
{
	return g_Babble3;
}

// �o�u���𔭐�������
void SetBabble3(int i, D3DXVECTOR2 pos)
{
	for (int j = 0; j < BABBLE_MAX; j++)
	{
		// �������g�p�̃f�[�^��T��
		if (g_Babble3[i][j].use == false)	// ���g�p��Ԃ̓G�f�[�^��������
		{
			g_Babble3[i][j].use = true;		// �g�p��Ԃ֕ύX����
			g_Babble3[i][j].pos = pos;
			g_Babble3[i][j].w = BABBLE_SIZE;
			g_Babble3[i][j].h = BABBLE_SIZE;

			g_Babble3[i][j].count = BABBLE_COUNT;

			g_Babble3[i][j].u = 0.0f;
			g_Babble3[i][j].v = 0.0f;
			g_Babble3[i][j].uh = 1.0f;
			g_Babble3[i][j].vh = 1.0f;

			// �o�������Ƃ���SE

			return;						// �G���Z�b�g�ł����̂ŏI������
		}
	}
}

// �X���C���̈ړ�
void MoveSlime3(int i)
{
	//���݈ʒu
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
				// ���� or 0
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
				// �
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

	//�ڕW�n�_
	D3DXVECTOR2 destination = D3DXVECTOR2(g_RouteSlimeX3[work] * CHIP_SIZE + (CHIP_SIZE / 2),
		g_RouteSlimeY3[work] * CHIP_SIZE + (CHIP_SIZE / 2));

	//����
	D3DXVECTOR2 components;

	//�傫��
	float magnitude;

	//�����i�P�ʃx�N�g���j
	D3DXVECTOR2 direction;

	//�����v�Z
	components.x = destination.x - position.x;
	components.y = destination.y - position.y;

	//�傫���v�Z
	magnitude = (float)sqrt(components.x * components.x + components.y * components.y);

	//�����v�Z�i���K���j
	direction.x = components.x / magnitude;
	direction.y = components.y / magnitude;

	//�ړ���̈ʒu���v�Z
	g_Slime3[i].pos.x += direction.x * g_Slime3[i].vel.x;
	g_Slime3[i].pos.y += direction.y * g_Slime3[i].vel.y;
}