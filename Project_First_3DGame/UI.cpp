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
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// キャラサイズ
#define TEXTURE_HEIGHT				(32)	// 
#define TEXTURE_MAX					(1)		// テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char* g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/TitleBG.png",
};


static bool			g_Use;						// true:使っている  false:未使用
static float		g_w, g_h;					// 幅と高さ
static XMFLOAT3		g_Pos;						// ポリゴンの座標
static int			g_TexNo;					// テクスチャ番号

static int			g_Score;					// スコア

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
