//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "UI.h"
#include "sprite.h"
#include "text.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(32)	// 
#define TEXTURE_MAX					(1)		// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/TitleBG.png",
};


static bool			g_Use;						// true:�g���Ă���  false:���g�p
static float		g_w, g_h;					// ���ƍ���
static XMFLOAT3		g_Pos;						// �|���S���̍��W
static int			g_TexNo;					// �e�N�X�`���ԍ�

static int			g_Score;					// �X�R�A

static BOOL			g_Load = FALSE;



HRESULT InitUI(void) {
	return S_OK;
}
void UninitUI(void) {

}
void UpdateUI(void) {
}
void DrawUI(void) {

}
