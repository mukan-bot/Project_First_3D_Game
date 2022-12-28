//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************

enum UI
{
	ATK_MAHOUZIN = 0,		// 魔法陣のレティクルてきなやつ
	ICON_MAHOUZIN,		// 右下のアイコン
	BLIND_MAHOUZIN,		// 右下のアイコンを隠す（クールダウン）

	UI_MAX,
};



//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct UI_ELEMENT{
	BOOL use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT2 pos;
	WHSIZE size;
	XMFLOAT2 t_pos;
	WHSIZE t_size;
	XMFLOAT4 color;
	char* TexturName;
	ID3D11ShaderResourceView* Texture;	// テクスチャ情報
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

//UIの要素を入れると使用未使用が入れ替わる
UI_ELEMENT* GetUI(UI index);
