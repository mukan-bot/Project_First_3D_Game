//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

using namespace DirectX;


void UpdateGameObject(void);	//GameObjectの更新（Updateの一番下に置く）

int SetGameObject(void);		//GameObjectを使う（戻り地はインデックス番号）
void DelGameObject(int index);	//GameObjectを破棄する（メモリの使用量は変わらない）


//セット・ゲット関数（indexはSetGameObjectの戻り値）

void SetPosition(int index, XMFLOAT3 position);
void SetRotation(int index, XMFLOAT3 rotation);
void SetScale(int index, XMFLOAT3 scale);
void SetGameObjectParent(int index, int parentIndex); 
void SetGameObjectZERO(int index);			//全ての値を0にする

XMFLOAT3 GetPosition(int index);
XMFLOAT3 GetRotation(int index);
XMFLOAT3 GetScale(int index);
int GetGameObjectParent(int index);