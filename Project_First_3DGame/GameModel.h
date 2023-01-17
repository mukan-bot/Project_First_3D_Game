//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGameModel(void);
void UninitGameModel(void);
void DrawGameModel(void);
//モデルをセットする
int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi, CULL_MODE cullMode);
//モデルを削除する
void DelGameModel(int index);
//モデルのスケールをセットする（GameObjectのscale*）
void SetGameModelScale(int index, XMFLOAT3 scale);
//モデルを直接いじりたい時用
DX11_MODEL* GetModel(int index);
//ワイヤーフレームで表示できるように
void SetGameModeFill(int index, D3D11_FILL_MODE model);
