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
#define	PLAYER_SIZE		(5.0f)				// 当たり判定の大きさ



void InitGameModel(void);
void UninitGameModel(void);
void DrawGameModel(void);
int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi, CULL_MODE cullMode);
void DelGameModel(int index);
void SetGameModelScale(int index, XMFLOAT3 scale);

DX11_MODEL* GetModel(int index);
void SetGameModeFill(int index, D3D11_FILL_MODE model);
