//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "EnemyHP.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "GameObject.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(ENEMY_MAX)			// �e�N�X�`���̐�
#define	MAX_ENEMY_HP_BAR		(125)		// �p�[�e�B�N���ő吔//TODO:��ŕς���

#define	ENEMY_HP_BAR_SIZE_X		(40.0f)		// ���_�T�C�Y
#define	ENEMY_HP_BAR_SIZE_Y		(40.0f)		// ���_�T�C�Y

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct ENEMY_HP_BAR_ELEMENT {
	bool use;		// �g���Ă��邩
	int objIndex;	// ���W�̏����p
	int type;
	MATERIAL material;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyHpBar(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// ���_�o�b�t�@

static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/effect01.png",
	"data/TEXTURE/effect01.png",
	"data/TEXTURE/effect01.png",
	"data/TEXTURE/effect01.png",
};

static BOOL						g_Load = FALSE;

static ENEMY_HP_BAR_ELEMENT g_element[MAX_ENEMY_HP_BAR];

//=============================================================================
// ����������
//=============================================================================
void InitEnemyHpBar(void){
	// ���_���̍쐬
	MakeVertexEnemyHpBar();

	// �e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++) {
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}
	//�p�[�e�B�N���̏����ݒ�
	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		ZeroMemory(&g_element[i].material, sizeof(g_element[i].material));
		g_element[i].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_element[i].use = false;
	}

	g_Load = TRUE;




	return;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyHpBar(void)
{
	if (g_Load == FALSE) return;

	//�e�N�X�`���̉��
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++) {
		if (g_Texture[nCntTex] != NULL) {
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer != NULL) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyHpBar(void) {
	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		if (!g_element[i].use) continue;
		// �Z�b�g�������̃I�u�W�F�N�g�������Ă���p�[�e�B�N��������
		g_element[i].use = GetGameObjectUse(g_element[i].objIndex);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyHpBar(void) {
	XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
	XMFLOAT4X4 camMtxView = GetCameraMtxView();


	// ���Z�����ɐݒ�
	SetBlendState(BLEND_MODE_ADD);

	// �t�H�O����
	SetFogEnable(false);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		if (g_element[i].use) {
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_element[i].type]);

			XMFLOAT3 pos = GetPosition(g_element[i].objIndex);
			XMFLOAT3 scl = GetScale(g_element[i].objIndex);
			//scl = MulXMFLOAT3(scl, SetXMFLOAT3(40));

			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �r���[�}�g���b�N�X���擾
			mtxView = XMLoadFloat4x4(&camMtxView);


			mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
			mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
			mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

			mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
			mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
			mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

			mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
			mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
			mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(scl.x, scl.y, scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// �}�e���A���ݒ�
			SetMaterial(g_element[i].material);

			// �|���S���̕`��
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// �ʏ�u�����h�ɖ߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// �t�H�O�L��
	SetFogEnable(true);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexEnemyHpBar(void) {
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	{//���_�o�b�t�@�̒��g�𖄂߂�
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = XMFLOAT3(-ENEMY_HP_BAR_SIZE_X / 2, ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[1].Position = XMFLOAT3(ENEMY_HP_BAR_SIZE_X / 2, ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[2].Position = XMFLOAT3(-ENEMY_HP_BAR_SIZE_X / 2, -ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[3].Position = XMFLOAT3(ENEMY_HP_BAR_SIZE_X / 2, -ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = { 0.0f, 0.0f };
		vertex[1].TexCoord = { 1.0f, 0.0f };
		vertex[2].TexCoord = { 0.0f, 1.0f };
		vertex[3].TexCoord = { 1.0f, 1.0f };

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// �}�e���A���J���[�̐ݒ�
//=============================================================================
void SetColorEnemyHpBar(int nIdxEnemyHpBar, XMFLOAT4 col) {
	g_element[nIdxEnemyHpBar].material.Diffuse = col;
}

//=============================================================================
// �p�[�e�B�N���̔�������
//=============================================================================
int SetEnemyHpBar(int objIndex, ENEMY_HP_BAR_TYPE type, XMFLOAT4 color) {
	int ans = -1;

	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		if (g_element[i].use) continue;

		g_element[i].use = true;
		g_element[i].objIndex = objIndex;
		g_element[i].type = type;
		g_element[i].material.Diffuse = color;
		ans = i;
		break;
	}
	return ans;
}