//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;				// 頂点情報

UI_ELEMENT g_UIelement[UI_MAX];



static BOOL g_Load = FALSE;


HRESULT InitUI(void) {

	ID3D11Device* pDevice = GetDevice();

	UI i;

	i = ATK_MAHOUZIN;
	g_UIelement[i].use = true;
	g_UIelement[i].size = WHSIZE(400, 400);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName,NULL,NULL,&g_UIelement[i].Texture,NULL);

	i = ICON_MAHOUZIN;
	g_UIelement[i].use = true;
	g_UIelement[i].size = WHSIZE(100, 100);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_WIDTH - 110 - 50, SCREEN_HEIGHT- 10 - 50);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin_icon.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName, NULL, NULL, &g_UIelement[i].Texture, NULL);

	i = BLIND_MAHOUZIN;		//TODO:画像をなんかいいのに変える
	g_UIelement[i].use = true;
	g_UIelement[i].size = WHSIZE(100, 100);
	g_UIelement[i].pos = XMFLOAT2(SCREEN_WIDTH - 110 - 50, SCREEN_HEIGHT - 10 - 50);
	g_UIelement[i].t_size = WHSIZE(1.0f, 1.0f);
	g_UIelement[i].t_pos = XMFLOAT2(0.0f, 0.0f);
	g_UIelement[i].color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	g_UIelement[i].TexturName = "./data/TEXTURE/mahouzin_icon.png";
	g_UIelement[i].Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), g_UIelement[i].TexturName, NULL, NULL, &g_UIelement[i].Texture, NULL);






	// 頂点バッファ生成
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

}
void DrawUI(void) {

	//SetAlphaTestEnable(true);

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
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	for (int i = 0; i < UI_MAX; i++) {
		if (!g_UIelement[i].use) continue;	//使われていなかったらスルー

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_UIelement[i].Texture);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, 
			g_UIelement[i].pos.x, g_UIelement[i].pos.y, 
			g_UIelement[i].size.w, g_UIelement[i].size.h, 
			g_UIelement[i].t_pos.x, g_UIelement[i].t_pos.y, 
			g_UIelement[i].t_size.w, g_UIelement[i].t_size.h,
			g_UIelement[i].color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// αテストを無効に
	SetAlphaTestEnable(false);
}



UI_ELEMENT* GetUI(UI index) {
	return &g_UIelement[index];
}