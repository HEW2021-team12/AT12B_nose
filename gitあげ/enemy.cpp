//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
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
// �}�N����`
//*****************************************************************************
#define ROT_SPD				(0.05f)
#define ENEMY_SPD			(2.0f)
#define ENEMY_SIZE			(55.0f)
#define MOVE_TIMER			(50)
#define SERCH_RANGE			(250.0f)
#define FIND_SPD			(2.0f)

#define SEARCH_TIMER		(CHIP_SIZE / ENEMY_SPD)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_EnemyTexture = 0;
static ENEMY g_Enemy;							  // �G�l�~�[�\����
static float MAPleft, MAPright, MAPtop, MAPunder; // �G�l�~�[�̍s���͈�
static int g_Enemy_Timer;
static int g_Search_Timer;
int move;
float g_U, g_V, g_Uh, g_Vh;
MOVE_STATE result;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	g_EnemyTexture = LoadTexture("data/TEXTURE/enemy.png");

	MAPleft = SCREEN_WIDTH / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_X / 2));
	MAPright = SCREEN_WIDTH / 2 - HALF_CHIP + CHIP_SIZE * ((MAP_SIZE_X / 2));

	MAPtop = SCREEN_HEIGHT / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_Y / 2));
	MAPunder = SCREEN_HEIGHT / 2 - HALF_CHIP + CHIP_SIZE * ((MAP_SIZE_Y / 2));

	// �G�l�~�[�\���̂̏�����
	g_Enemy.use   = true;
	g_Enemy.w     = ENEMY_SIZE;
	g_Enemy.h     = ENEMY_SIZE;
	g_Enemy.pos   = D3DXVECTOR2(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 150.0f);
	g_Enemy.rot   = 0.0f;
	g_Enemy.vel   = D3DXVECTOR2(ENEMY_SPD,ENEMY_SPD);

	g_Enemy_Timer = 0;
	g_Search_Timer = 0;

	// �G�l�~�[UV
	g_U = 0.0f;
	g_V = 0.0f;
	g_Uh = 0.0f;
	g_Vh = 0.0f;
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{

	if (g_Enemy.use == true)
	{
		// �ǐՔ���
		if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
		{// ������(�͈͓��ɓ�����)

			// �G�l�~�[��CHIP_SIZE���ړ������瓮��
			if (g_Search_Timer <= 0)
			{
				g_Search_Timer = (int)SEARCH_TIMER;

				// �V�ŃT�[�`
				{

					int Ex = 0, Ey = 0;
					int Px = 0, Py = 0;

					// �G�l�~�[�̃}�b�v���W����
					{
						float sx, sy;

						// ����
						for (int x = 0; x < MAP_SIZE_X; x++)
						{
							sx = SCREEN_WIDTH / 2 + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);

							if (g_Enemy.pos.x < sx + CHIP_SIZE && // �v���C���[���A�}�b�v��
								g_Enemy.pos.x > sx)				  // �v���C���[��A�}�b�v��
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
						// �c��
						for (int y = 0; y < MAP_SIZE_Y; y++)
						{
							sy = SCREEN_HEIGHT / 2 + CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

							if (g_Enemy.pos.y < sy + CHIP_SIZE && // �v���C���[���A�}�b�v��
								g_Enemy.pos.y > sy)				  // �v���C���[��A�}�b�v��
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

					// �v���C���[�̃}�b�v���W����
					{
						D3DXVECTOR2 Ppos = GetPlayerPosition();

						float sx, sy;

						// ����
						for (int x = 0; x < MAP_SIZE_X; x++)
						{
							sx = SCREEN_WIDTH / 2 + (HALF_CHIP / 6 * 5) + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);

							if (Ppos.x < sx + CHIP_SIZE && // �v���C���[���A�}�b�v��
								Ppos.x > sx)				  // �v���C���[��A�}�b�v��
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
						// �c��
						for (int y = 0; y < MAP_SIZE_Y; y++)
						{
							sy = SCREEN_HEIGHT / 2 + /*(HALF_CHIP / 3)*/ +CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

							if (Ppos.y < sy + CHIP_SIZE && // �v���C���[���A�}�b�v��
								Ppos.y > sy)			   // �v���C���[��A�}�b�v��
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

					// �V�ŃT�[�`
					// �����₱�����̈����������������H
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

			// ���ŃT�[�`
			{
			//���݈ʒu
			D3DXVECTOR2 position = g_Enemy.pos;

			//�ڕW�n�_
			D3DXVECTOR2 destination = GetPlayerPosition();

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

			// ���̈ړ��ʂ̕����傫���Ƃ�
			if (fabsf(direction.x) > fabsf(direction.y))
			{
				// ���ɍs���Ƃ�
				if (direction.x < 0)
				{
					g_U = 1.0f;
					g_V = 0.0f;
					g_Uh = -0.5f;
					g_Vh = 0.5f;
				}
				else // �E�ɍs���Ƃ�
				{
					g_U = 0.5f;
					g_V = 0.0f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
			}
			else // �c�̈ړ��ʂ̕����傫�� or �����Ƃ�
			{
				// ��ɍs���Ƃ�
				if (direction.y < 0)
				{
					g_U = 0.5f;
					g_V = 0.5f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
				else // ���ɍs���Ƃ�
				{
					g_U = 0.0f;
					g_V = 0.5f;
					g_Uh = 0.5f;
					g_Vh = 0.5f;
				}
			}

			//�ړ���̈ʒu���v�Z
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
		// �����Ă��Ȃ�
		else 
		{
			g_Enemy_Timer++;

			if (g_Enemy_Timer > MOVE_TIMER)
			{
				move = rand() % 5;
				g_Enemy_Timer = 0;
				srand((unsigned)time(NULL));
			}

			// �G�l�~�[�ړ�
			// 1:��@2:���@3:�E�@4:���@0:�Ȃ�(�ҋ@)
			if (move == 1) // ��
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

			if (move == 2) // ��
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

			if (move == 3) // �E
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

			if (move == 4) // ��
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

			if (move == 0) // �ҋ@
			{
				g_U = 0.0f;
				g_V = 0.0f;
				g_Uh = 0.5f;
				g_Vh = 0.5f;
			}

		}
		// ���ˏ���
		// ���[
		//if (g_Enemy.pos.x <= MAPleft)
		//{
		//	g_Enemy.pos.x = MAPleft;
		//}
		//// �E�[
		//if (g_Enemy.pos.x >= MAPright)
		//{
		//	g_Enemy.pos.x = MAPright;
		//}
		//// ��[
		//if (g_Enemy.pos.y <= MAPtop)
		//{
		//	g_Enemy.pos.y = MAPtop;
		//}
		//// ���[
		//if (g_Enemy.pos.y >= MAPunder)
		//{
		//	g_Enemy.pos.y = MAPunder;
		//}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	if (g_Enemy.use == true)
	{
		//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
		float px = g_Enemy.pos.x;	// �G�l�~�[�̕\���ʒuX
		float py = g_Enemy.pos.y;	// �G�l�~�[�̕\���ʒuY
		float pw = g_Enemy.w;		// �G�l�~�[�̕\����
		float ph = g_Enemy.h;		// �G�l�~�[�̕\������
		D3DXCOLOR col;

		if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
		{
			col = D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		DrawSpriteColorRotate(g_EnemyTexture,px, py, pw, ph,
			g_U, g_V,
			g_Uh, g_Vh,
			col, g_Enemy.rot);
	}
}

//=============================================================================
// �G�l�~�[�\���̂̐擪�A�h���X���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy;
}


//=============================================================================
// �G�̔�������
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos)
{
	// �������g�p�̃f�[�^��T��
	if (g_Enemy.use == false)		// ���g�p��Ԃ̓G�f�[�^��������
	{
		g_Enemy.use = true;			// �g�p��Ԃ֕ύX����
		g_Enemy.pos = pos;			// ���W���Z�b�g
		g_Enemy.rot = 0.0f;			// ��]�p�̃��Z�b�g
		return;						// �G���Z�b�g�ł����̂ŏI������
	}
	
}

bool SerchPlayer(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos)
{
	D3DXVECTOR2 maxRange, minRange;

	minRange.x = Enemypos.x - SERCH_RANGE;
	minRange.y = Enemypos.y - SERCH_RANGE;
	maxRange.x = Enemypos.x + SERCH_RANGE;
	maxRange.y = Enemypos.y + SERCH_RANGE;

	//X���̔���
	if (minRange.x < Playerpos.x &&
		maxRange.x > Playerpos.x)
	{
		//Y���̔���
		if (minRange.y < Playerpos.y &&
			maxRange.y > Playerpos.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}