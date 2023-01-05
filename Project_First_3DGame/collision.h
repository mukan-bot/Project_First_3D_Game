//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum COLLISION_TYPE
{
	TYPE_BB,	//バウンディングボックス
	TYPE_BC,	//バウンディングサークル
};

enum COLLISION_LAYER 
{
	LAYER_PLAYER,		// プレイヤーの体
	LAYER_PLAYER_ATK,	// プレイヤーの攻撃
	LAYER_ENEMY,		// エネミーの体
	LAYER_ENEMY_ATK,	// エネミーの攻撃
	LAYER_OBSTACLE,		// マップに配置する障害物
	LAYER_FIELD,
};

#define COLLISION_MAX (512)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct COLLISION
{
	bool use;				// 使っているか
	bool ans;				// 当たっているかを保存
	int gameObjectIndex;	// ポジションを参照する
	COLLISION_TYPE type;	// 当たり判定のタイプを保存
	COLLISION_LAYER layer;	// 当たり判定のレーヤーを保存
#ifdef _DEBUG
	int gameModelIndex;		//デバックのときに当たり判定表示できるように
#endif // _DEBUG

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//collisionのセット
int SetCollision(COLLISION_LAYER layer, COLLISION_TYPE type);
//collisionの削除
void DelCollision(int index);
//collisionで使用しているGameObjectのインデックスの所得
int GetColObjectIndex(int index);
//collisionの当たり判定の結果の所得（場所によっては判定がずれる）
bool GetColAns(int index);
//現在の当たり判定の結果の所得（重くなりがち）
bool GetColAnsUpdate(int index);

void InitCollision(void);
void UpdateCollision(void);
