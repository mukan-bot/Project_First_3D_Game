//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "renderer.h"

#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LIGHT	g_Light[LIGHT_MAX];

static FOG		g_Fog;

static	BOOL	g_FogEnable = false;


//=============================================================================
// ����������
//=============================================================================
void InitLight(void)
{

	//���C�g������
	for (int i = 0; i < LIGHT_MAX; i++)
	{
		g_Light[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Light[i].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
		g_Light[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[i].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		g_Light[i].Attenuation = 100.0f;	// ��������
		g_Light[i].Type = LIGHT_TYPE_NONE;	// ���C�g�̃^�C�v
		g_Light[i].Enable = false;			// ON / OFF
		SetLight(i, &g_Light[i]);
	}

	// ���s�����̐ݒ�i���E���Ƃ炷���j
	g_Light[0].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);		// ���̌���
	g_Light[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	g_Light[0].Type = LIGHT_TYPE_DIRECTIONAL;					// ���s����
	g_Light[0].Enable = false;									// ���̃��C�g��ON
	SetLight(0, &g_Light[0]);									// ����Őݒ肵�Ă���

	// �v���C���[�Ǐ]�|�C���g���C�g
	g_Light[1].Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);		//�|�C���g���C�g����������͓K��
	g_Light[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	g_Light[1].Type = LIGHT_TYPE_POINT;						// �|�C���g���C�g
	g_Light[1].Attenuation = 50.0f;	// ��������
	g_Light[1].Enable = true;								// ���̃��C�g��ON
	g_Light[1].Position = GetPosition(GetPlayerGameObjectIndex());	//Position��ݒ�	
	SetLight(1, &g_Light[1]);								// ����Őݒ肵�Ă���

	// �t�H�O�̏������i���̌��ʁj
	g_Fog.FogStart = 100.0f;									// ���_���炱�̋��������ƃt�H�O��������n�߂�
	g_Fog.FogEnd = 400.0f;									// �����܂ŗ����ƃt�H�O�̐F�Ō����Ȃ��Ȃ�
	g_Fog.FogColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);		// �t�H�O�̐F
	SetFog(&g_Fog);
	SetFogEnable(g_FogEnable);

}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateLight(void)
{


	g_Light[1].Position = GetPosition(GetPlayerGameObjectIndex());	//Position��ݒ�	
	SetLight(1, &g_Light[1]);								// ����Őݒ肵�Ă���

}


//=============================================================================
// ���C�g�̐ݒ�
//=============================================================================
void SetLightData(int index, LIGHT* light)
{
	SetLight(index, light);
}


LIGHT* GetLightData(int index)
{
	return(&g_Light[index]);
}


//=============================================================================
// �t�H�O�̐ݒ�
//=============================================================================
void SetFogData(FOG* fog)
{
	SetFog(fog);
}


BOOL GetFogEnable(void)
{
	return(g_FogEnable);
}



