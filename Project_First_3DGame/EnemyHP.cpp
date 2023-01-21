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
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(ENEMY_MAX)			// テクスチャの数
#define	MAX_ENEMY_HP_BAR		(125)		// パーティクル最大数//TODO:後で変える

#define	ENEMY_HP_BAR_SIZE_X		(40.0f)		// 頂点サイズ
#define	ENEMY_HP_BAR_SIZE_Y		(40.0f)		// 頂点サイズ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct ENEMY_HP_BAR_ELEMENT {
	bool use;		// 使われているか
	int objIndex;	// 座標の所得用
	int type;
	MATERIAL material;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyHpBar(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// 頂点バッファ

static ID3D11ShaderResourceView* g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

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
// 初期化処理
//=============================================================================
void InitEnemyHpBar(void){
	// 頂点情報の作成
	MakeVertexEnemyHpBar();

	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++) {
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}
	//パーティクルの初期設定
	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		ZeroMemory(&g_element[i].material, sizeof(g_element[i].material));
		g_element[i].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_element[i].use = false;
	}

	g_Load = TRUE;




	return;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyHpBar(void)
{
	if (g_Load == FALSE) return;

	//テクスチャの解放
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++) {
		if (g_Texture[nCntTex] != NULL) {
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	// 頂点バッファの解放
	if (g_VertexBuffer != NULL) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyHpBar(void) {
	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		if (!g_element[i].use) continue;
		// セットした時のオブジェクトが消えてたらパーティクルも消す
		g_element[i].use = GetGameObjectUse(g_element[i].objIndex);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyHpBar(void) {
	XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
	XMFLOAT4X4 camMtxView = GetCameraMtxView();


	// 加算合成に設定
	SetBlendState(BLEND_MODE_ADD);

	// フォグ無効
	SetFogEnable(false);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	for (int i = 0; i < MAX_ENEMY_HP_BAR; i++) {
		if (g_element[i].use) {
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_element[i].type]);

			XMFLOAT3 pos = GetPosition(g_element[i].objIndex);
			XMFLOAT3 scl = GetScale(g_element[i].objIndex);
			//scl = MulXMFLOAT3(scl, SetXMFLOAT3(40));

			// ワールドマトリックスの初期化
			mtxWorld = XMMatrixIdentity();

			// ビューマトリックスを取得
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

			// スケールを反映
			mtxScl = XMMatrixScaling(scl.x, scl.y, scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// 移動を反映
			mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&mtxWorld);

			// マテリアル設定
			SetMaterial(g_element[i].material);

			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// 通常ブレンドに戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// フォグ有効
	SetFogEnable(true);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEnemyHpBar(void) {
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	{//頂点バッファの中身を埋める
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = XMFLOAT3(-ENEMY_HP_BAR_SIZE_X / 2, ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[1].Position = XMFLOAT3(ENEMY_HP_BAR_SIZE_X / 2, ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[2].Position = XMFLOAT3(-ENEMY_HP_BAR_SIZE_X / 2, -ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);
		vertex[3].Position = XMFLOAT3(ENEMY_HP_BAR_SIZE_X / 2, -ENEMY_HP_BAR_SIZE_Y / 2, 0.0f);

		// 法線の設定
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = { 0.0f, 0.0f };
		vertex[1].TexCoord = { 1.0f, 0.0f };
		vertex[2].TexCoord = { 0.0f, 1.0f };
		vertex[3].TexCoord = { 1.0f, 1.0f };

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// マテリアルカラーの設定
//=============================================================================
void SetColorEnemyHpBar(int nIdxEnemyHpBar, XMFLOAT4 col) {
	g_element[nIdxEnemyHpBar].material.Diffuse = col;
}

//=============================================================================
// パーティクルの発生処理
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