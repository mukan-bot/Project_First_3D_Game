//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "text.h"

#include <stdio.h>

// �}�N����`

#define TEXTURE_WIDTH				(80)	// �T�C�Y
#define TEXTURE_HEIGHT				(120)	// 
#define TEXTURE_MAX					(2)		// �e�N�X�`���̐�

#define TEXTURE_PATTERN_DIVIDE_X	(62)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����

//�\���̒�`
struct TEXT_PRIVATE
{
	XMFLOAT2	pos;		// �|���S���̍��W
	float		w, h;		// ���ƍ���

	float tw = 0.0207333333333333f;	// �e�N�X�`���̕�
	float th = 0.0823333333333333f;	// �e�N�X�`���̍���
	float tx = 0.00f;	// �e�N�X�`���̍���X���W
	float ty = 0.00f;	// �e�N�X�`���̍���Y���W
	XMFLOAT4	color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	bool use = FALSE;
};



// �O���[�o���ϐ�
static ID3D11Buffer* g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����


static char* g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/font.png",
};


static BOOL	g_Load = FALSE;		// ���������s�������̃t���O
static TEXT_PRIVATE	g_TEXT[TEXT_MAX];

char g_textlist[293][48][3] = {//�g���镶����
	{"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
	}, {"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
	}, {"��","��","��","��","��","��","��","��","��",
	}, {"�A","�C","�E","�G","�I","�J","�L","�N","�P","�R","�T","�V","�X","�Z","�\","�^","�`","�c","�e","�g","�i","�j","�k","�l","�m","�n","�q","�t","�w","�z","�}","�~","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
	}, {"�K","�M","�O","�Q","�S","�U","�W","�Y","�[","�]","�_","�a","�d","�f","�h","�o","�r","�u","�x","�{","�p","�s","�v","�y","�|",
	}, {"�@","�B","�D","�F","�H","�b","��","��","��",
	}, {"�A","�B","�[","�`","�u","�v","�y","�z","�w","�x","�J","�K",
	}, {"��","��","��","��","��","��","��","��","��","��","��","��","��","��","�d","�c","�E","��","��","��","�~","��",
	}, {"�I","�h","��","��","��","��","�f","�i","�j","��","~","�b","�M","�o","�{","��","�p","��","��","�H","�Q","�|","�O","\\","��","�m","�G","�F","�n","�C","�D","�^",
	}, {"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
	}, {"�`","�a","�b","�c","�d","�e","�f","�g","�h","�i","�j","�k","�l","�m","�n","�o","�p","�q","�r","�s","�t","�u","�v","�w","�x","�y",
	}, {"�O","�P","�Q","�R","�S","�T","�U","�V","�W","�X","�@"
	}
};
//�����������������������������������ĂƂȂɂʂ˂̂͂Ђӂւق܂݂ނ߂����������������
//�������������������������Âłǂ΂тԂׂڂς҂Ղ؂�
//����������������
//�A�C�E�G�I�J�L�N�P�R�T�V�X�Z�\�^�`�c�e�g�i�j�k�l�m�n�q�t�w�z�}�~��������������������������������
//�K�M�O�Q�S�U�W�Y�[�]�_�a�d�f�h�o�r�u�x�{�p�s�v�y�|
//�@�B�D�F�H�b������
//�A�B�[�`�u�v�y�z�w�x�J�K
//��󁡁����������������������d�c�E���恦�~��
//�I�h���������f�i�j��~�b�M�o�{���p�����H�Q�|�O\���m�G�F�n�C�D�^\
//����������������������������������������������������
//�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y
//�O�P�Q�R�S�T�U�V�W�X

char g_textlist_half[293][48][3] = {
	{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z", }, {
	"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",}, {
	"1","2","3","4","5","6","7","8","9"," "
	},
};


//=============================================================================
// ����������
//=============================================================================
HRESULT Init_text(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	for (int i = 0; i < TEXT_MAX; i++) {
		g_TEXT[i].pos = XMFLOAT2(0.0f, 0.0f);	// ���S�_����\��
		g_TEXT[i].w = TEXTURE_WIDTH;
		g_TEXT[i].h = TEXTURE_HEIGHT;
		//48���P�Q����������P�Ŋ����ăe�N�X�`���̕������߂�
		g_TEXT[i].tw = 1 / 48.0f;
		g_TEXT[i].th = 1 / 12.0f;
		g_TEXT[i].use = FALSE;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit_text(void)
{

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Load = FALSE;
}




// �`�揈��
void Draw_text(void)
{
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

	for (int i = 0; i < TEXT_MAX; i++) {
		if (g_TEXT[i].use) {
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);


			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, g_TEXT[i].pos.x, g_TEXT[i].pos.y, g_TEXT[i].w, g_TEXT[i].h, g_TEXT[i].tx, g_TEXT[i].ty, g_TEXT[i].tw, g_TEXT[i].th, g_TEXT[i].color);

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);

			g_TEXT[i].use = FALSE;

		}
	}
}


//�e�L�X�g�̕\��(�S�p�̂�)�����~
void SetText(TEXT text_p, char text[]) {
	text_p.pos.x -= ((strlen(text) - 1) * (text_p.size / 2)) / 2;
	for (int i = 0; i < strlen(text); i++) {
		for (int j = 0; j < 293; j++) {
			for (int l = 0; l < 48; l++) {
				//�S�p�����𔻒�
				if ((int)text[i] == (int)g_textlist[j][l][0] && (int)text[i + 1] == (int)g_textlist[j][l][1]) {
					for (int z = 0; z < TEXT_MAX; z++) {
						if (!g_TEXT[z].use) {
							g_TEXT[z].color = text_p.color;
							g_TEXT[z].pos = text_p.pos;
							g_TEXT[z].w = text_p.size;
							g_TEXT[z].color = text_p.color;

							g_TEXT[z].h = (text_p.size / 8) * 12;//�������P�Q������size�����Ɍv�Z	
							g_TEXT[z].pos.x += (text_p.size / 2) * i;
							g_TEXT[z].use = TRUE;
							g_TEXT[z].tx = g_TEXT[z].tw * l;	// �e�N�X�`���̍���X���W
							g_TEXT[z].ty = g_TEXT[z].th * j;	// �e�N�X�`���̍���Y���W
							i++;
							break;
						}
					}
				}
			}
		}
	}
}
//����
void SetText_d(TEXT text_p, int d) {
	char text[TEXT_MAX];
	char temp[10][3] = { "�O","�P", "�Q", "�R", "�S", "�T", "�U", "�V", "�W", "�X", };
	_itoa_s(d, text, 10);
	int i = 0;
	int j = d;
	while (j != 0) {
		j /= 10;
		i++;
	}
	text_p.pos.x += (((text_p.size) * i) / 2) - text_p.size / 2;
	while (d != 0) {
		SetText(text_p, temp[d % 10]);
		d /= 10;
		text_p.pos.x -= text_p.size;
	}
}