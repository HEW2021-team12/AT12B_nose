//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_MAX		(1)			// �G�l�~�[��Max�l��

// �G�l�~�[�\����
struct ENEMY
{
	bool					use;		// true:�g���Ă���  false:���g�p
	float					w, h;		// ���ƍ���
	D3DXVECTOR2				pos;		// �|���S���̍��W
	float					rot;		// �|���S���̉�]��
	D3DXVECTOR2				vel;		// �ړ���
};


// AI�̈ړ��̏��
enum MOVE_STATE
{
	MOVE_NONE = 0 , // �������Ȃ�
	MOVE_UP,		// �������
	MOVE_DOWN,		// ��������
	MOVE_RIGHT,		// �E������
	MOVE_LEFT,		// ��������
	
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
void SetEnemy(D3DXVECTOR2 pos);
bool SerchPlayer(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos);
