/*==============================================================================

   ���_�Ǘ� [player.cpp]
	Author :	�^�@���� �Îs
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_PlayerTexture = 0;
PLAYER		g_Player;
float		control_timer;
float		gravity_timer;
float		vertigo_timer;

float		g_DrawGrav = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	g_PlayerTexture = LoadTexture("data/TEXTURE/player1.png");

	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = SCREEN_HEIGHT / 2;
	g_Player.size.x = PLAYER_SIZE;
	g_Player.size.y = PLAYER_SIZE;
	g_Player.vel.x = PLAYER_SPD;
	g_Player.vel.y = PLAYER_SPD;
	g_Player.rot = 0.0f;
	g_Player.rot_vel = 0.1f;
	control_timer = 0.0f;
	gravity_timer = 0.0f;
	g_Player.vertigo_isUse = false;
	vertigo_timer = 0.0f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	/*if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}*/
	

	if (g_Player.rot <= -2.0f || g_Player.rot >= 3.0f)
	{
		g_Player.vertigo_isUse = true;
	}

	if (g_Player.vertigo_isUse == false)
	{
		ZeroGravity();
		ControlPlayer();
		FramePlayer();
	}

	if (g_Player.vertigo_isUse == true)
	{
		vertigo_timer ++;
	}

	if (vertigo_timer >= 100.0f)
	{
		g_Player.vertigo_isUse = false;
		g_Player.rot = 0.0f;
		vertigo_timer = 0.0f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	DrawSpriteColorRotate(g_PlayerTexture,
		g_Player.pos.x, g_Player.pos.y + g_DrawGrav,
		g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f,
		1.0f,1.0f,
		col, g_Player.rot);
}

void ControlPlayer(void)
{
	if (!GetKeyboardPress(DIK_LEFT))
	{
				
	}

	if (!GetKeyboardPress(DIK_RIGHT))
	{

	}

	if (!GetKeyboardPress(DIK_UP))
	{

	}

	if (!GetKeyboardPress(DIK_DOWN))
	{

	}


	//��(�ړ�)
	if (GetKeyboardPress(DIK_LEFT)
		|| IsButtonPressed(0, BUTTON_LEFT))
	{
		g_Player.pos.x -= g_Player.vel.x;

		g_Player.vel.x = g_Player.vel.x + 0.01f;

		if (g_Player.vel.x >= 3.0f)
		{
			g_Player.vel.x = 3.0f;
		}
		/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y),
			D3DXVECTOR2(g_Player.size.x, g_Player.size.y))
			== 1)
			g_Player.pos.x += g_Player.vel.x;*/

		control_timer++;
		if (control_timer >= 20.0f)
		{
			g_Player.rot -= g_Player.rot_vel;
			control_timer = 0.0f;
		}
	}

	//�E(�ړ�)
	if (GetKeyboardPress(DIK_RIGHT)
		|| IsButtonPressed(0, BUTTON_RIGHT))
	{
		g_Player.pos.x += g_Player.vel.x;

		g_Player.vel.x = g_Player.vel.x + 0.01f;

		if (g_Player.vel.x >= 3.0f)
		{
			g_Player.vel.x = 3.0f;
		}
		/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y),
			D3DXVECTOR2(g_Player.size.x, g_Player.size.y))
			== 1)
			g_Player.pos.x -= g_Player.vel.x;*/

		control_timer++;
		if (control_timer >= 20.0f)
		{
			g_Player.rot += g_Player.rot_vel;
			control_timer = 0.0f;
		}
	}

	//��(�ړ�)
	if (GetKeyboardPress(DIK_UP)
		|| IsButtonPressed(0, BUTTON_UP))
	{
		g_Player.pos.y -= g_Player.vel.y;

		g_Player.vel.y = g_Player.vel.y + 0.01f;

		if (g_Player.vel.y >= 3.0f)
		{
			g_Player.vel.y = 3.0f;
		}
		/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y - 1.0f),
			D3DXVECTOR2(g_Player.size.x, g_Player.size.y))
			== 1)
		{
			g_Player.pos.y += g_Player.vel.y;
		}*/
	}

	//��(�ړ�)
	if (GetKeyboardPress(DIK_DOWN)
		|| IsButtonPressed(0, BUTTON_DOWN))
	{
		g_Player.pos.y += g_Player.vel.y;

		g_Player.vel.y = g_Player.vel.y + 0.01f;

		if (g_Player.vel.y >= 3.0f)
		{
			g_Player.vel.y = 3.0f;
		}
		/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + 1.0f),
			D3DXVECTOR2(g_Player.size.x, g_Player.size.y))
			== 1)
		{
			g_Player.pos.y -= g_Player.vel.y;
		}*/
	}

	//����]
	if (GetKeyboardPress(DIK_Q)
		|| IsButtonPressed(0, BUTTON_L2))
	{
		g_Player.rot -= 0.01f;
	}

	//�E��]
	if (GetKeyboardPress(DIK_E)
		|| IsButtonPressed(0, BUTTON_R2))
	{
		g_Player.rot += 0.01f;
	}

}

void ZeroGravity(void)
{
	if (gravity_timer < 20.0f)
	{
		g_DrawGrav -= GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 20.0f && gravity_timer < 40.0f)
	{
		g_DrawGrav += GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 40.0f && gravity_timer < 60.0f)
	{
		g_DrawGrav += GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 60.0f && gravity_timer < 80.0f)
	{
		g_DrawGrav -= GRAVITY_VEL;
		gravity_timer++;
	}

	if (gravity_timer >= 80.0f)
	{
		gravity_timer = 0.0f;
	}
}

void FramePlayer(void)
{
	//��(�g)
	if (g_Player.pos.x <= 0.0f + (g_Player.size.x / 2))
	{
		g_Player.pos.x = 0.0f + (g_Player.size.x / 2);
	}
	//�E(�g)
	if (g_Player.pos.x >= SCREEN_WIDTH - (g_Player.size.x / 2))
	{
		g_Player.pos.x = SCREEN_WIDTH - (g_Player.size.x / 2);
	}

	//��(�g)
	if (g_Player.pos.y <= 0.0f + (g_Player.size.y / 2))
	{
		g_Player.pos.y = 0.0f + (g_Player.size.y / 2);
	}
	//��(�g)
	if (g_Player.pos.y >= SCREEN_HEIGHT - (g_Player.size.y / 2))
	{
		g_Player.pos.y = SCREEN_HEIGHT - (g_Player.size.y / 2);
	}
}

PLAYER* GetPlayer(void)
{
	return &g_Player;
}

D3DXVECTOR2 GetPlayerPosition(void)
{
	return g_Player.pos;
}