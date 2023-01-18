//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX	(20)



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

// エネミーの配置
void SetEnemy(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);
// 何体のENEMYが生きてるか
int GetAliveEnemy(void);
// エネミーのGameObjectIndexの所得（使用されていないインデクスを指定された場合-1を返す）
int GetEnemyIndex(int index);
// エネミーのHPを所得
int GetEnemyHP(int index);
// エネミーのHPをセット
void SetEnemyHP(int index, int hp);