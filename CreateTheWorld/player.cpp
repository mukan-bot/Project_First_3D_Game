//=============================================================================
//
// モデル処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/Kirby_Body.obj"			// 読み込むモデル名
#define	MODEL_PLAYER_LEG_L	"data/MODEL/Kirby_Leg_L.obj"			// 読み込むモデル名
#define	MODEL_PLAYER_LEG_R	"data/MODEL/Kirby_Leg_R.obj"			// 読み込むモデル名
#define	MODEL_PLAYER_ARM_L	"data/MODEL/Kirby_Arm_L.obj"			// 読み込むモデル名
#define	MODEL_PLAYER_ARM_R	"data/MODEL/Kirby_Arm_R.obj"			// 読み込むモデル名

#define	VALUE_MOVE			(2.0f)							// 移動量
#define	VALUE_ROTATE		(XM_PI * 0.02f)					// 回転量

#define PLAYER_SHADOW_SIZE	(1.0f)							// 影の大きさ
#define PLAYER_OFFSET_Y		(5.0f)							// プレイヤーの足元をあわせる

#define PLAYER_PARTS_MAX	(4)								// プレイヤーのパーツの数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER		g_Player;						// プレイヤー

static PLAYER		g_Parts[PLAYER_PARTS_MAX];		// プレイヤーのパーツ用


// プレイヤーの階層アニメーションデータ
// プレイヤーの頭を左右に動かしているアニメデータ
static INTERPOLATION_DATA move_tbl_right[] = {	// pos, rot, scl, frame

	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI / 5, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI / 5, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA move_tbl_left[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI / 5, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI / 5, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA move_tbl_IdleParts[]{
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};
static INTERPOLATION_DATA move_tbl_IdleMain[]{
	{ XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA* g_MoveTblAdr[] =
{
	move_tbl_right,
	move_tbl_left,
	move_tbl_IdleParts,
	move_tbl_IdleMain,

};



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LoadModel(MODEL_PLAYER, &g_Player.model);
	g_Player.load = true;

	g_Player.pos = { 0.0f, PLAYER_OFFSET_Y, 0.0f };
	g_Player.rot = { 0.0f, 0.0f, 0.0f };
	g_Player.scl = { 0.05f, 0.05f, 0.05f };

	g_Player.spd = 0.0f;			// 移動スピードクリア
	g_Player.size = PLAYER_SIZE;	// 当たり判定の大きさ

	g_Player.use = true;

	// ここでプレイヤー用の影を作成している
	XMFLOAT3 pos = g_Player.pos;
	pos.y -= (PLAYER_OFFSET_Y - 0.1f);
	//          ↑
	//        このメンバー変数が生成した影のIndex番号
	// 階層アニメーション用の初期化処理
	g_Player.parent = NULL;			// 本体（親）なのでNULLを入れる

	// 階層アニメーション用のメンバー変数の初期化
	g_Player.time = 0.0f;			// 線形補間用のタイマーをクリア
	g_Player.tblNo = 0;			// 再生する行動データテーブルNoをセット
	g_Player.tblMax = 0;			// 再生する行動データテーブルのレコード数をセット
	g_Parts[0].tblMax = 0;			// 再生する行動データテーブルのレコード数をセット




	// パーツの初期化
	for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
		g_Parts[i].use = false;

		// 位置・回転・スケールの初期設定
		g_Parts[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Parts[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Parts[i].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

		// 親子関係
		g_Parts[i].parent = &g_Player;		// ← ここに親のアドレスを入れる

		// 階層アニメーション用のメンバー変数の初期化
		g_Parts[i].time = 0.0f;			// 線形補間用のタイマーをクリア
		g_Parts[i].tblNo = 0;			// 再生する行動データテーブルNoをセット
		g_Parts[i].tblMax = 0;			// 再生する行動データテーブルのレコード数をセット

		// パーツの読み込みはまだしていない
		g_Parts[i].load = 0;
	}


	g_Parts[0].use = true;
	// 位置・回転・スケールの初期設定
	g_Parts[0].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[0].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[0].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// 親子関係
	g_Parts[0].parent = &g_Player;		// ← ここに親のアドレスを入れる

	// 階層アニメーション用のメンバー変数の初期化
	g_Parts[0].time = 0.0f;			// 線形補間用のタイマーをクリア
	g_Parts[0].tblNo = 0;			// 再生する行動データテーブルNoをセット
	g_Parts[0].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

	// パーツの読み込み
	LoadModel(MODEL_PLAYER_LEG_L, &g_Parts[0].model);
	g_Parts[0].load = true;



	g_Parts[1].use = true;
	// 位置・回転・スケールの初期設定
	g_Parts[1].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[1].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[1].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// 親子関係
	g_Parts[1].parent = &g_Player;		// ← ここに親のアドレスを入れる

	// 階層アニメーション用のメンバー変数の初期化
	g_Parts[1].time = 0.0f;			// 線形補間用のタイマーをクリア
	g_Parts[1].tblNo = 1;			// 再生する行動データテーブルNoをセット
	g_Parts[1].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

	// パーツの読み込み
	LoadModel(MODEL_PLAYER_LEG_R, &g_Parts[1].model);
	g_Parts[1].load = true;


	g_Parts[2].use = true;
	// 位置・回転・スケールの初期設定
	g_Parts[2].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[2].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[2].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// 親子関係
	g_Parts[2].parent = &g_Player;		// ← ここに親のアドレスを入れる

	// 階層アニメーション用のメンバー変数の初期化
	g_Parts[2].time = 0.0f;			// 線形補間用のタイマーをクリア
	g_Parts[2].tblNo = 0;			// 再生する行動データテーブルNoをセット
	g_Parts[2].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

	// パーツの読み込み
	LoadModel(MODEL_PLAYER_ARM_L, &g_Parts[2].model);
	g_Parts[2].load = true;



	g_Parts[3].use = true;
	// 位置・回転・スケールの初期設定
	g_Parts[3].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[3].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[3].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// 親子関係
	g_Parts[3].parent = &g_Player;		// ← ここに親のアドレスを入れる

	// 階層アニメーション用のメンバー変数の初期化
	g_Parts[3].time = 0.0f;			// 線形補間用のタイマーをクリア
	g_Parts[3].tblNo = 1;			// 再生する行動データテーブルNoをセット
	g_Parts[3].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

	// パーツの読み込み
	LoadModel(MODEL_PLAYER_ARM_R, &g_Parts[3].model);
	g_Parts[3].load = true;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// モデルの解放処理
	if (g_Player.load)
	{
		UnloadModel(&g_Player.model);
		g_Player.load = false;
	}
	// モデルの解放処理
	for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
		if (g_Parts[i].load)
		{
			UnloadModel(&g_Parts[i].model);
			g_Parts[i].load = false;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{


#ifdef _DEBUG
#endif


	//	// Key入力があったら移動処理する
	if (g_Player.spd > 0.0f)
	{
		//プレイヤーのアニメーションをアイドルにする
		g_Player.tblNo = 0;
		g_Player.tblMax = 0;

		// 階層アニメーション用のメンバー変数の初期化
		g_Parts[0].tblNo = 0;			// 再生する行動データテーブルNoをセット
		g_Parts[0].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

		// 階層アニメーション用のメンバー変数の初期化
		g_Parts[1].tblNo = 1;			// 再生する行動データテーブルNoをセット
		g_Parts[1].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

		// 階層アニメーション用のメンバー変数の初期化
		g_Parts[2].tblNo = 0;			// 再生する行動データテーブルNoをセット
		g_Parts[2].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

		// 階層アニメーション用のメンバー変数の初期化
		g_Parts[3].tblNo = 1;			// 再生する行動データテーブルNoをセット
		g_Parts[3].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// 再生する行動データテーブルのレコード数をセット

		//プレイヤーの移動

		
		// 入力のあった方向へプレイヤーを向かせて移動させる
		g_Player.pos.x -= sinf(g_Player.rot.y) * g_Player.spd;
		g_Player.pos.z -= cosf(g_Player.rot.y) * g_Player.spd;
	}

	else {
		//プレイヤーのアニメーションをアイドルにする
		g_Player.tblNo = 3;
		g_Player.tblMax = sizeof(move_tbl_IdleMain) / sizeof(INTERPOLATION_DATA);
		for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
			g_Parts[i].time = 0.0f;
			g_Parts[i].tblNo = 3;
			g_Parts[i].tblMax = sizeof(move_tbl_IdleParts) / sizeof(INTERPOLATION_DATA);
		}
	}

	g_Player.spd *= 0.5f;


	// 階層アニメーション
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		// 使われているなら処理する
		if ((g_Parts[i].use == true) && (g_Parts[i].tblMax > 0))
		{	// 線形補間の処理
			int nowNo = (int)g_Parts[i].time;			// 整数分であるテーブル番号を取り出している
			int maxNo = g_Parts[i].tblMax;				// 登録テーブル数を数えている
			int nextNo = (nowNo + 1) % maxNo;			// 移動先テーブルの番号を求めている
			INTERPOLATION_DATA* tbl = g_MoveTblAdr[g_Parts[i].tblNo];	// 行動テーブルのアドレスを取得

			XMVECTOR nowPos = XMLoadFloat3(&tbl[nowNo].pos);	// XMVECTORへ変換
			XMVECTOR nowRot = XMLoadFloat3(&tbl[nowNo].rot);	// XMVECTORへ変換
			XMVECTOR nowScl = XMLoadFloat3(&tbl[nowNo].scl);	// XMVECTORへ変換

			XMVECTOR Pos = XMLoadFloat3(&tbl[nextNo].pos) - nowPos;	// XYZ移動量を計算している
			XMVECTOR Rot = XMLoadFloat3(&tbl[nextNo].rot) - nowRot;	// XYZ回転量を計算している
			XMVECTOR Scl = XMLoadFloat3(&tbl[nextNo].scl) - nowScl;	// XYZ拡大率を計算している

			float nowTime = g_Parts[i].time - nowNo;	// 時間部分である少数を取り出している

			Pos *= nowTime;								// 現在の移動量を計算している
			Rot *= nowTime;								// 現在の回転量を計算している
			Scl *= nowTime;								// 現在の拡大率を計算している

			// 計算して求めた移動量を現在の移動テーブルXYZに足している＝表示座標を求めている
			XMStoreFloat3(&g_Parts[i].pos, nowPos + Pos);

			// 計算して求めた回転量を現在の移動テーブルに足している
			XMStoreFloat3(&g_Parts[i].rot, nowRot + Rot);

			// 計算して求めた拡大率を現在の移動テーブルに足している
			XMStoreFloat3(&g_Parts[i].scl, nowScl + Scl);

			// frameを使て時間経過処理をする
			g_Parts[i].time += 1.0f / tbl[nowNo].frame;	// 時間を進めている
			if ((int)g_Parts[i].time >= maxNo)			// 登録テーブル最後まで移動したか？
			{
				g_Parts[i].time -= maxNo;				// ０番目にリセットしつつも小数部分を引き継いでいる
			}

		}

	}






#ifdef _DEBUG	// デバッグ情報を表示する
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	//縁取り
	SetFuchi(1);


	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// スケールを反映
	mtxScl = XMMatrixScaling(g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(g_Player.rot.x, g_Player.rot.y + XM_PI, g_Player.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	XMStoreFloat4x4(&g_Player.mtxWorld, mtxWorld);


	// モデル描画
	DrawModel(&g_Player.model);


	//MEMO:ここで階層アニメーションをしている。
	// パーツの階層アニメーション
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_Parts[i].scl.x, g_Parts[i].scl.y, g_Parts[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_Parts[i].rot.x, g_Parts[i].rot.y, g_Parts[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_Parts[i].pos.x, g_Parts[i].pos.y, g_Parts[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		if (g_Parts[i].parent != NULL)	// 子供だったら親と結合する
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_Parts[i].parent->mtxWorld));
			// ↑
			// g_Player.mtxWorldを指している
		}

		//自分の子供のパーツのために（描画で使うワールド）
		XMStoreFloat4x4(&g_Parts[i].mtxWorld, mtxWorld);

		// 使われているなら処理する。ここまで処理している理由は他のパーツがこのパーツを参照している可能性があるから。
		if (g_Parts[i].use == false) continue;

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);


		// モデル描画
		DrawModel(&g_Parts[i].model);



	}

	//縁取り
	SetFuchi(0);

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player;
}

