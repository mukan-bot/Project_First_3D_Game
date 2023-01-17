//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "UI.h"
#include "enemy.h"
#include "text.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;				// ���_���

UI_ELEMENT g_UIelement[UI_MAX];



static BOOL g_Load = FALSE;


HRESULT InitUI(void) {

	ID3D11Device* pDevice = GetDevice();


	//���ꂼ�ꏉ���ݒ�
	UI i;

	i = ATK_MAHOUZIN;
	g_UIelement[i].use = false;
	g_UIelement[i].size = WHSIZE(400, 400);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName,NULL,NULL,&g_UIelement[i].Texture,NULL);

	i = ICON_MAHOUZIN;
	g_UIelement[i].use = false;
	g_UIelement[i].size = WHSIZE(100, 100);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_WIDTH - 110 - 50, SCREEN_HEIGHT- 10 - 50);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin_icon.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName, NULL, NULL, &g_UIelement[i].Texture, NULL);

	i = BLIND_MAHOUZIN;		//TODO:�摜���Ȃ񂩂����̂ɕς���
	g_UIelement[i].use = false;
	g_UIelement[i].size = WHSIZE(100, 100);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_WIDTH - 110 - 50, SCREEN_HEIGHT - 10 - 50);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin_icon.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName, NULL, NULL, &g_UIelement[i].Texture, NULL);






	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	g_Load = TRUE;



	return S_OK;
}
void UninitUI(void) {
	//���[�h����Ă�����J������
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < UI_MAX; i++)
	{
		if (g_UIelement[i].Texture)
		{
			g_UIelement[i].Texture->Release();
			g_UIelement[i].Texture = NULL;
		}
	}

	g_Load = FALSE;
}
void UpdateUI(void) {

	//ENEMY�����̎c���Ă��邩��\������
	TEXT text;
	text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	text.pos = XMFLOAT2(180.0f, 30.0f);
	text.size = 30;
	SetText(text, "�`�k�h�u�d�@�d�m�d�l�x");
	text.pos = XMFLOAT2(400.0f, 30.0f);
	SetText_d(text, GetAliveEnemy());

	//�v���C���[�̎c��HP
	text.pos = XMFLOAT2(180.0f, 70.0f);
	SetText(text, "�o�k�`�x�d�q �g�o");
	text.pos = XMFLOAT2(400.0f, 70.0f);
	SetText_d(text, GetPlayerHP());

}
void DrawUI(void) {

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	for (int i = 0; i < UI_MAX; i++) {
		if (!g_UIelement[i].use) continue;	//�g���Ă��Ȃ�������X���[

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_UIelement[i].Texture);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, 
			g_UIelement[i].pos.x, g_UIelement[i].pos.y, 
			g_UIelement[i].size.w, g_UIelement[i].size.h, 
			g_UIelement[i].t_pos.x, g_UIelement[i].t_pos.y, 
			g_UIelement[i].t_size.w, g_UIelement[i].t_size.h,
			g_UIelement[i].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);
}



UI_ELEMENT* GetUI(UI index) {
	return &g_UIelement[index];
}