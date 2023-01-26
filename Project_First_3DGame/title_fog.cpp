//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "title_bg.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(1)				// テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;				// 頂点情報
static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char* g_TexturName[TEXTURE_MAX] = {
	//"./data/TEXTURE/Dissolve.png",
	"./data/TEXTURE/title_fog.png",
};


static BOOL	g_use;		// TRUE:使っている  FALSE:未使用

static int g_TexNo;		// テクスチャ番号

static BOOL g_Load = FALSE;

static WHSIZE g_porigonSize = WHSIZE(SCREEN_WIDTH*4, SCREEN_HEIGHT*3);

static XMFLOAT2 g_UV[2];


HRESULT InitTitleFOG(void) {

	ID3D11Device* pDevice = GetDevice();

	//テクスチャ生成
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


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// 変数の初期化
	g_use = TRUE;

	g_TexNo = 0;

	g_Load = TRUE;

	g_UV[0] = XMFLOAT2(0.0f, 0.0f);
	g_UV[1] = XMFLOAT2(0.5f, 0.3f);

	return S_OK;
}
void UninitTitleFOG(void) {
	if (g_Load == FALSE) return;

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
void UpdateTitleFOG(void) {
	g_UV[0].x += 0.0005f;
	g_UV[0].y += 0.0005f;
	g_UV[1].x -= 0.0006f;
	g_UV[1].y -= 0.0004f;
	//g_UV[1] = XMFLOAT2(0.5f, 0.3f);
}
void DrawTitleFOG(void) {
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.7f);
	material.DissolveAlpha = 1.0f;
	SetMaterial(material);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteLeftTop(g_VertexBuffer, 0.0f, 0.0f, g_porigonSize.w, g_porigonSize.h, g_UV[0].x, g_UV[0].y, 1.0f, 1.0f);
	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
	SetSpriteLeftTop(g_VertexBuffer, 0.0f, 0.0f, g_porigonSize.w, g_porigonSize.h, g_UV[1].x, g_UV[1].y, 1.0f, 1.0f);
	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}