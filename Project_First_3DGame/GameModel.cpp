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
#define MAX_MODEL	(512)	//とりあえず256個にしておく

struct GameModel{
	bool is_load;				// ロードされているか（モデルが）
	int is_fuchi;				// 縁取りをするか
	int gameObjectIndex;		// PosとかRot、Sclを所得する
	XMFLOAT3 ofsetScale;		// Sclの調整用
	CULL_MODE cullMode;			// カリングモード
	XMFLOAT4X4 mtxWorld;		// 
	DX11_MODEL model;			// 
	bool use;					// GameModelが使われているか
	D3D11_FILL_MODE fillMode;	// 塗りをどうするか
};



//グローバル変数
GameModel g_gameModel[MAX_MODEL];



//=============================================================================
// 初期処理
//=============================================================================
void InitGameModel(void){
	//ゲームモデルの初期化
	for (int i = 0; i < MAX_MODEL; i++) {
		g_gameModel[i].gameObjectIndex = -1;
		g_gameModel[i].is_load = false;
		g_gameModel[i].is_fuchi = 0;
		g_gameModel[i].cullMode = CULL_MODE_NUM;
		g_gameModel[i].ofsetScale = SetXMFLOAT3(1.0f);
		g_gameModel[i].use = false;
	}
}



//=============================================================================
// 終了処理
//=============================================================================
void UninitGameModel (void){
	// モデルの解放処理
	for (int i = 0; i < MAX_MODEL; i++) {
		{
			UnloadModel(&g_gameModel[i].model);
			g_gameModel[i] .is_load = false;
		}
		if (g_gameModel[i].use) {
			g_gameModel[i].use = false;
		}
	}
}



//=============================================================================
// 描画処理
//=============================================================================
void DrawGameModel(void){
	for (int i = 0; i < MAX_MODEL; i++) {
		// 使われていないなら処理を飛ばす
		if (!g_gameModel[i].use) continue;

		// 必要な情報を所得
		XMFLOAT3 pos = GetPosition(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 rot = GetRotation(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 scl = GetScale(g_gameModel[i].gameObjectIndex);
		// スケールを調整
		scl = MulXMFLOAT3(scl, g_gameModel[i].ofsetScale);

		// 塗りを変更
		SetPixelFill(g_gameModel[i].fillMode);

#ifdef _DEBUG
		// デバック版のみワイヤーフレームですべてを表示できるようにする
		if (GetInputPress(MOVE_JUMP)) {
			SetPixelFill(D3D11_FILL_WIREFRAME);
		}
#endif // _DEBUG

		// カリング
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

	}

	// ワイヤーフレームから戻す
	SetPixelFill(D3D11_FILL_SOLID);

	//縁設定戻す
	SetFuchi(0);

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);


}





int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi,CULL_MODE cullMode) {
	int ans = -1;

	for (int i = 0; i < MAX_MODEL; i++) {
		//使われているのなら飛ばす
		if (g_gameModel[i].use) continue;
		if (strcmp(modelPath, "NO") != 0) {	//モデルを使用しない時（GetModelで頑張る時）
			LoadModel(modelPath, &g_gameModel[i].model);
			g_gameModel[i].is_load = true;
		}

		g_gameModel[i].gameObjectIndex = gameObjectIndex;
		g_gameModel[i].is_fuchi = fuchi;
		g_gameModel[i].cullMode = cullMode;

		g_gameModel[i].fillMode = D3D11_FILL_SOLID;

		g_gameModel[i].use = true;

		ans = i;
		break;
	}
#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetGameModelで-1が返されました");
	}
#endif // _DEBUG

	return ans;
}

void DelGameModel(int index) {
	// 指定されたモデルが読み込まれていたら削除
	if (g_gameModel[index].is_load)
	{
		UnloadModel(&g_gameModel[index].model);
		g_gameModel[index].is_load = false;
	}
	// useを書き換え
	g_gameModel[index].use = false;
}


void SetGameModelScale(int index, XMFLOAT3 scale) {
	g_gameModel[index].ofsetScale = scale;
}

DX11_MODEL* GetModel(int index) {
	return &g_gameModel[index].model;
}

void SetGameModeFill(int index, D3D11_FILL_MODE model){
	g_gameModel[index].fillMode = model;
}