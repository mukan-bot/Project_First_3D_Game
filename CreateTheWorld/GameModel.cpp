//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "GameModel.h"


//マクロ定義
#define MAX_MODEL	(256)	//とりあえず256個にしておく

struct GameModel{
	bool is_load;
	DX11_MODEL model;
	int is_fuchi;
	CULL_MODE cullMode;
	int gameObjectIndex;
	XMFLOAT4X4 mtxWorld;
	bool use;
};



//グローバル変数
GameModel g_gameModel[MAX_MODEL];



//=============================================================================
// 初期処理
//=============================================================================
void InitGameModel(void){
	for (int i = 0; i < MAX_MODEL; i++) {
		g_gameModel[i].gameObjectIndex = -1;
		g_gameModel[i].is_load = false;
		g_gameModel[i].is_fuchi = 0;
		g_gameModel[i].cullMode = CULL_MODE_NUM;
		g_gameModel[i].use = false;
	}
}



//=============================================================================
// 終了処理
//=============================================================================
void UninitGameModel (void){
	// モデルの解放処理
	for (int i = 0; i < MAX_MODEL; i++) {
		if (g_gameModel[i].is_load)
		{
			UnloadModel(&g_gameModel[i] .model);
			g_gameModel[i] .is_load = false;
		}
	}
}




//=============================================================================
// 描画処理
//=============================================================================
void DrawGameModel(void){
	for (int i = 0; i < MAX_MODEL; i++) {
		if (!g_gameModel[i].use) continue;

		XMFLOAT3 pos = GetPosition(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 rot = GetRotation(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 scl = GetScale(g_gameModel[i].gameObjectIndex);



		// カリング無効
		SetCullingMode(g_gameModel[i].cullMode);

		//縁設定
		SetFuchi(g_gameModel[i].is_fuchi);


		XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(scl.x, scl.y, scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y + XM_PI, rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_gameModel[i].mtxWorld, mtxWorld);


		// モデル描画
		DrawModel(&g_gameModel[i].model);

		//縁設定戻す
		SetFuchi(0);

		// カリング設定を戻す
		SetCullingMode(CULL_MODE_BACK);

	}
}





int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi,CULL_MODE cullMode) {
	int ans = -1;
	for (int i = 0; i < MAX_MODEL; i++) {
		if (g_gameModel[i].use) continue;

		LoadModel(modelPath, &g_gameModel[i].model);
		g_gameModel[i].is_load = true;

		g_gameModel[i].gameObjectIndex = gameObjectIndex;
		g_gameModel[i].is_fuchi = fuchi;
		g_gameModel[i].cullMode = cullMode;

		g_gameModel[i].use = true;

		ans = i;
		break;
	}
	return ans;
}

void DelGameModel(int index) {
	if (g_gameModel[index].is_load)
	{
		UnloadModel(&g_gameModel[index].model);
		g_gameModel[index].is_load = false;
	}
	g_gameModel[index].use = false;
}