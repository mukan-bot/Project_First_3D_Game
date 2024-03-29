//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "renderer.h"

#include "player.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LIGHT	g_Light[LIGHT_MAX];

static FOG		g_Fog;

static	BOOL	g_FogEnable = false;


//=============================================================================
// 初期化処理
//=============================================================================
void InitLight(void)
{

	//ライト初期化
	for (int i = 0; i < LIGHT_MAX; i++)
	{
		g_Light[i].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Light[i].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
		g_Light[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[i].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		g_Light[i].Attenuation = 100.0f;	// 減衰距離
		g_Light[i].Type = LIGHT_TYPE_NONE;	// ライトのタイプ
		g_Light[i].Enable = false;			// ON / OFF
		SetLight(i, &g_Light[i]);
	}

	// 並行光源の設定（世界を照らす光）
	g_Light[0].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);		// 光の向き
	g_Light[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.10f);	// 光の色
	g_Light[0].Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	g_Light[0].Enable = false;									// このライトをON
	SetLight(0, &g_Light[0]);									// これで設定している

	// 視点追従スポットライト
	g_Light[1].Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);		//向き
	g_Light[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);	// 光の色(あたってるのがわかりやすいように色を変えている)
	g_Light[1].Type = LIGHT_TYPE_SPOTLIGHT;					// スポットライト
	g_Light[1].Attenuation = 40.0f;	// 減衰距離
	g_Light[1].Enable = true;								// このライトをON
	g_Light[1].Position = GetPosition(GetPlayerGameObjectIndex());	//Positionを設定	
	SetLight(1, &g_Light[1]);								// これで設定している

	// プレイヤー追従ポイントライト
	g_Light[2].Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);		//ポイントライトだから向きは適当
	g_Light[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	g_Light[2].Type = LIGHT_TYPE_POINT;						// ポイントライト
	g_Light[2].Attenuation = 50.0f;	// 減衰距離
	g_Light[2].Enable = true;								// このライトをON
	g_Light[2].Position = GetPosition(GetPlayerGameObjectIndex());	//Positionを設定	
	SetLight(2, &g_Light[2]);								// これで設定している

	// フォグの初期化（霧の効果）
	g_Fog.FogStart = 100.0f;									// 視点からこの距離離れるとフォグがかかり始める
	g_Fog.FogEnd = 400.0f;									// ここまで離れるとフォグの色で見えなくなる
	g_Fog.FogColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);		// フォグの色
	SetFog(&g_Fog);
	SetFogEnable(g_FogEnable);

}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateLight(void)
{
	//視点追従スポットライトの向きと座標を更新
	{
		XMFLOAT3 pRot = GetRotation(GetPlayerGameObjectIndex());
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vec.x += sinf(pRot.x);
		vec.z += cosf(pRot.x);
		vec.y -= tanf(pRot.z);
		vec = NormalizeXMFLOAT3(vec);
		g_Light[1].Direction = vec;
		XMFLOAT3 pPos = GetPosition(GetCameraIndex());
		pPos.y = 1;					//完全に視点に合わせるとスポットライトっぽく見えないので足元から照らす
		g_Light[1].Position = pPos;	//Positionを設定(カメラの位置に指定)
		SetLight(1, &g_Light[1]);
	}
	//プレイヤー追従ポイントライトの座標を更新
	{
		g_Light[2].Position = GetPosition(GetPlayerGameObjectIndex());	//Positionを設定
		SetLight(2, &g_Light[2]);								// これで設定している
	}

}


//=============================================================================
// ライトの設定
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
// フォグの設定
//=============================================================================
void SetFogData(FOG* fog)
{
	SetFog(fog);
}


BOOL GetFogEnable(void)
{
	return(g_FogEnable);
}



