//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

// プレイヤーのGameObjectのインデックスを所得
int GetPlayerGameObjectIndex(void);
// プレイヤーのコリジョンのGameObjectのインデックスを所得
int GetPlayerColObjectIndex(void);
// プレイヤーの攻撃系の当たり判定のGameObjectのインデックスを所得
int GetPlayerHitColObjectIndex(void);
// プレイヤーのHPを所得
int GetPlayerHP(void);