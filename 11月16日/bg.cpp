//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : �Îs
//
//=============================================================================
#include "bg.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
struct MAP_DATA_T 
{
	D3DXVECTOR2 uv;			//UV�l
	int			stop = 0;	//�N���\�t���O(1�͐i���֎~)

};

MAP_DATA_T g_MapInfo[3] =
{
	{ {0.625f,   0.0f}, 0},//�n��
	{ {0.250f, 0.0f}, 0},  //�Ȃɂ��Ȃ�
	{ {0.625f, 0.625f}, 0},//�؂芔
};


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_map_obj[MAP_SIZE_Y][MAP_SIZE_X] = {

	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
	
};

//�}�b�v�̓����蔻��p�f�[�^
int g_map_hitchk[MAP_SIZE_Y][MAP_SIZE_X] =
{
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};

static int g_Ground = 0;		// �w�i�p�e�N�X�`�����
static int g_Back = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(void)
{
	g_Ground = LoadTexture("data/TEXTURE/basechip.png");
	g_Back = LoadTexture("data/TEXTURE/back.jpg");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	// �w�i
	DrawSpriteLeftTop(g_Back, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	////�}�b�v�̕\��
	//for (int y = 0; y < MAP_SIZE_Y; y++)
	//{
	//	for (int x = 0; x < MAP_SIZE_X; x++)
	//	{
	//		float sx, sy;

	//		sx = SCREEN_WIDTH  / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);
	//		sy = SCREEN_HEIGHT / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);
	//		DrawSprite(g_Ground,
	//			sx, sy,
	//			CHIP_SIZE, CHIP_SIZE, 
	//			0.0f, 0.0f, 0.125f, 0.125f);
	//	}
	//}

	////�I�u�W�F�N�g�̕\��
	//for (int y = 0; y < MAP_SIZE_Y; y++)
	//{
	//	for (int x = 0; x < MAP_SIZE_X; x++)
	//	{
	//		MAP_DATA_T mapchip;
	//		mapchip = g_MapInfo[ g_map_obj[y][x] ];

	//		float sx, sy;
	//		sx = SCREEN_WIDTH  / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);
	//		sy = SCREEN_HEIGHT / 2 + HALF_CHIP + CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

	//		DrawSprite(g_Ground,
	//			sx, sy,
	//			CHIP_SIZE, CHIP_SIZE,
	//			mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
	//	}
	//}
}

// �}�b�v�̓����蔻�� 1�����^�[�������Ɖ����Ԃ�
int GetMapEnter(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	D3DXVECTOR2 min, max;
	
	min.x = pos.x - size.x / 2;
	min.y = pos.y - size.y / 2;
	max.x = pos.x + size.x / 2;
	max.y = pos.y + size.y / 2;

	int gx = 0;
	int gy = 0;

	float sx, sy;
	
	// ����
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		sx = SCREEN_WIDTH / 2 + (HALF_CHIP / 6 * 5) + CHIP_SIZE * ((-MAP_SIZE_X / 2) + x);

		if (min.x < sx + CHIP_SIZE && // �v���C���[���A�}�b�v��
			max.x > sx)				  // �v���C���[��A�}�b�v��
		{
			gx = x;
		}
	}

	// �c��
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		sy = SCREEN_HEIGHT / 2 + (HALF_CHIP / 3) + CHIP_SIZE * ((-MAP_SIZE_Y / 2) + y);

		if (min.y < sy + CHIP_SIZE && // �v���C���[���A�}�b�v��
			max.y > sy)				  // �v���C���[��A�}�b�v��
		{
			gy = y;
		}
	}

	return g_map_hitchk[gy][gx];
}

int GetMap(int x, int y)
{
	return g_map_hitchk[y][x];
}