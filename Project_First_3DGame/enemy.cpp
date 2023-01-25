//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "enemy.h"
#include "player.h"
#include "collision.h"
#include "attack.h"
#include "sound.h"
#include "sprite.h"
#include "camera.h"


#define MODEL_PATH			("./data/MODEL/Skull/skull.obj")
#define MODEL_PARTS_PATH	("./data/MODEL/Skull/jaw.obj")

#define MOVE_ROT_ANGLE		(180)
#define MOVE_ROT_SPEED		(30)
#define MOVE_LENGTH			(10)
#define MOVE_FRONT_SPEED	(30)

#define ATK_DELAY		(60)	//プレイヤーを見つけてから(口を開けてから)60F後に攻撃を発射
#define LOOK_PLAYER		(XMFLOAT3(40.0f,40.0f,40.0f))	//プレイヤーを探知できる範囲

#define BAR_TEXTURE			("./data/TEXTURE/WhiteOut.png")	// バーのテクスチャー（色変えで使用）
#define BAR_SIZE_WIDTH		(6)	// バーのサイズ横
#define BAR_SIZE_HEIGHT		(1)	// バーのサイズ縦
#define BAR_OFFSET_Y		(4)		// バーを表示する座標のoffset
#define BAR_COLOR_1			(XMFLOAT4(1.0f,0.0f,0.0f,1.0f))	// HPバーの下の色
#define BAR_COLOR_2			(XMFLOAT4(0.0f,1.0f,0.0f,1.0f))	// HPバーの残量
#define BAR_SHOW_LEN		(45)	// バーが表示される距離（PLAYERとエネミー間）

#define ENEMY_DEATH_COUNT	(60)	// エネミーの死亡シーンの長さ
enum ENEMY_STATE{
	ENEMY_STOP,
	ENEMY_ROTATION,
	ENEMY_CALCULATION,
	ENEMY_MOVE,
	ENEMY_ATK,
	ENEMY_DEATH,
	ENEMY_STATE_MAX
};


struct ENEMY{
	bool use;
	bool isMove;	//移動状態かどうか
	int objIndex;
	int colIndex;
	int hitColIndex;
	int modelIndex;
	int modelPartsIndex;
	int objPartsIndex;
	int HP;
	//行動patternを作るために使う
	ENEMY_STATE state;
	int count;
	//移動とか回転に使う
	XMFLOAT3 rot;
	XMFLOAT3 pos1;
	XMFLOAT3 pos2;
	XMFLOAT3 vec;
	//コリジョンのoffset
	XMFLOAT3 c_pos;
	XMFLOAT3 c_size;
	//攻撃
	bool isATK;		//攻撃してるか
	int atkCount;	//攻撃までのカウントダウン

	//HPバーの表示
	WHSIZE barSize;
	MATERIAL material;
	ID3D11Buffer* vertexBuffer1;	//HPバーの残量の頂点バッファー
	ID3D11Buffer* vertexBuffer2;	//HPバーの残量の頂点バッファー
};


//グローバル変数
ENEMY g_enemy[20];
int g_pObjectIndex;	// プレイヤーのオブジェクトインデックスを所得
XMFLOAT3 g_pPos;	// プレイヤーの座標を保存する

static ID3D11Buffer* g_VertexBuffer = NULL;	//HPバーの全体量の頂点バッファ


static ID3D11ShaderResourceView* g_Texture = NULL;


//プロトタイプ宣言
void LookPlayer(ENEMY* enemy);	// プレイヤーが近くに要るかを判断
HRESULT MakeVertexEnemyHpBar(ID3D11Buffer** vertexBuffer, float fWidth, float fHeight);

HRESULT InitEnemy(void) {

	g_pObjectIndex = GetPlayerGameObjectIndex();

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].objIndex = SetGameObject();
		SetPosition(g_enemy[i].objIndex, XMFLOAT3(0.0f, -1000.0f, 0.0f));	//見えない所に生成しておく
		g_enemy[i].modelIndex = SetGameModel(MODEL_PATH, g_enemy[i].objIndex, 0, CULL_MODE_BACK);

		g_enemy[i].objPartsIndex = SetGameObject();
		SetGameObjectParent(g_enemy[i].objPartsIndex, g_enemy[i].objIndex);
		g_enemy[i].modelPartsIndex = SetGameModel(MODEL_PARTS_PATH, g_enemy[i].objPartsIndex, 0, CULL_MODE_BACK);
		SetGameObjectZERO(g_enemy[i].objPartsIndex);

		g_enemy[i].colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
		g_enemy[i].hitColIndex = SetCollision(LAYER_ENEMY, TYPE_BC);

		g_enemy[i].c_size = XMFLOAT3(0.5f, 0.5f, 0.5f);	//collisionのサイズ
		g_enemy[i].c_pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
		g_enemy[i].HP = 100;
		g_enemy[i].use = false;

		g_enemy[i].state = ENEMY_STOP;
		g_enemy[i].rot = SetXMFLOAT3(0.0f);
		g_enemy[i].count = 0;

		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);
		int index;
		index = GetColObjectIndex(g_enemy[i].colIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));
		index = GetColObjectIndex(g_enemy[i].hitColIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

		// 頂点バッファ生成
		//MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer1, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);
		//MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer2, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);

		// マテリアル
		ZeroMemory(&g_enemy[i].material, sizeof(g_enemy[i].material));
		g_enemy[i].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_enemy[i].material.DissolveAlpha = 1.0f;
	}
	// 頂点バッファ生成
	MakeVertexEnemyHpBar(&g_VertexBuffer, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);
	//HPバー用のテクスチャの読み込み
	g_Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), BAR_TEXTURE, NULL, NULL, &g_Texture, NULL);

	return S_OK;
}

void UninitEnemy(void) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].use = false;
		DelCollision(g_enemy[i].colIndex);
		DelCollision(g_enemy[i].hitColIndex);
		DelGameObject(g_enemy[i].objIndex);
		DelGameObject(g_enemy[i].objPartsIndex);
	}
}

void UpdateEnemy(void) {

	//ループ外でできることはループの外でやる
	g_pPos = GetPosition(g_pObjectIndex);
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].use) continue;

		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);

		bool isOK = true;

		//パーツ
		{
			SetGameObjectZERO(g_enemy[i].objPartsIndex);	// 一応０にしておく
			if (g_enemy[i].isATK) {							// 攻撃中だったら口を開けるモーションをする
				SetPosition(g_enemy[i].objPartsIndex, XMFLOAT3(0.0f, -0.2f, 0.0f));
				SetRotation(g_enemy[i].objPartsIndex, XMFLOAT3(-0.5f, 0.0f, 0.0f));
			}
		}

		// エネミーが攻撃中じゃないまたは死んでないなら攻撃できる範囲にプレイヤーが居るか確認
		if (g_enemy[i].state != ENEMY_ATK) {
			LookPlayer(&g_enemy[i]);
		}


		//移動
		{
			switch (g_enemy[i].state)
			{
			case ENEMY_STOP:// 回転量を計算
				g_enemy[i].rot.y = DegToRad(((rand() % MOVE_ROT_ANGLE) - MOVE_ROT_ANGLE / 2) / MOVE_ROT_SPEED);
				g_enemy[i].state = ENEMY_ROTATION;
				g_enemy[i].count = MOVE_ROT_SPEED;
				break;
			case ENEMY_ROTATION:// エネミーを回転
				if (g_enemy[i].count > 0) {
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].count--;
				}
				else {
					g_enemy[i].state = ENEMY_CALCULATION;
				}
				break;
			case ENEMY_CALCULATION:// 移動できるか計算
				g_enemy[i].pos1 = g_enemy[i].pos2 = GetPosition(g_enemy[i].objIndex);
				
				for (int j = 0; j < MOVE_LENGTH; j++) {
					g_enemy[i].pos2.x += sinf(rot.y);
					g_enemy[i].pos2.z += cosf(rot.y);
					SetPosition(GetColObjectIndex(g_enemy[i].colIndex), g_enemy[i].pos2);
					if (GetColAnsUpdate(g_enemy[i].colIndex)) {
						g_enemy[i].state = ENEMY_STOP;
						isOK = false;
						break;
					}
				}
				if (isOK) {
					g_enemy[i].state = ENEMY_MOVE;
					g_enemy[i].vec = SubXMFLOAT3(g_enemy[i].pos2, g_enemy[i].pos1);
					g_enemy[i].vec = DivXMFLOAT3(g_enemy[i].vec, SetXMFLOAT3(MOVE_FRONT_SPEED));
					g_enemy[i].count = MOVE_FRONT_SPEED;
				}
				SetPosition(GetColObjectIndex(g_enemy[i].colIndex), g_enemy[i].pos1);	//コリジョンの場所を元に戻す
				break;
			case ENEMY_MOVE:// 移動
				if (g_enemy[i].count > 0) {
					pos.x += g_enemy[i].vec.x;
					pos.y += g_enemy[i].vec.y;
					pos.z += g_enemy[i].vec.z;
					g_enemy[i].count--;

				}
				else {
					g_enemy[i].state = ENEMY_CALCULATION;
				}
				break;
			case ENEMY_ATK:// 攻撃
				if (g_enemy[i].atkCount < 0) {
					if (g_enemy[i].atkCount > -30) {
						SetAttack(ATK_ENEMY_1, g_enemy[i].objIndex);	//MEMO:こうするとしばらく口の中に溜まっているように見えるはず
					}
					if(g_enemy[i].atkCount < -ATK_DELAY) {
						g_enemy[i].state = ENEMY_CALCULATION;
						g_enemy[i].isATK = false;
					}
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].rot.y -= 0.01f;
					g_enemy[i].atkCount--;
				}
				else {	//ATK_DELAYの回数分待つ
					g_enemy[i].atkCount--;
					//回転させる（徐々に早く）
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].rot.y += 0.01f;
				}
				break;
			case ENEMY_DEATH:
				if (g_enemy[i].count < 0) {
					DelGameObject(g_enemy[i].objIndex);
					DelGameModel(g_enemy[i].modelIndex);
					DelGameModel(g_enemy[i].modelPartsIndex);
					DelGameObject(g_enemy[i].objPartsIndex);
					g_enemy[i].use = false;
				}
				else {
					g_enemy[i].count--;
					float a = GetGameModelDissolve(g_enemy[i].modelIndex);
					a -= 1.0f / ENEMY_DEATH_COUNT;
					OutputDebug("%f", a);
					SetGameModelDissolve(g_enemy[i].modelIndex, a);
					SetGameModelDissolve(g_enemy[i].modelPartsIndex, a);
				}
				break;
			case ENEMY_STATE_MAX:
				break;
			default:
				break;
			}
			//更新
			SetPosition(g_enemy[i].objIndex, pos);
			SetRotation(g_enemy[i].objIndex, rot);
			SetScale(g_enemy[i].objIndex, scl);

		}



		//当たり判定
		{
			if (g_enemy[i].HP > -1) {
				int index;
				index = GetColObjectIndex(g_enemy[i].colIndex);
				SetPosition(index, AddXMFLOAT3(pos, g_enemy[i].c_pos));
				SetRotation(index, rot);
				SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));
				index = GetColObjectIndex(g_enemy[i].hitColIndex);
				SetPosition(index, AddXMFLOAT3(pos, g_enemy[i].c_pos));
				SetRotation(index, rot);
				SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

				if (GetColAnsUpdate(g_enemy[i].hitColIndex)) {
					g_enemy[i].HP--;
				}
				if (g_enemy[i].HP <= 0) {
					//HPが０になったら音を鳴らしてエネミーを削除する
					g_enemy[i].state = ENEMY_DEATH;
					g_enemy[i].count = ENEMY_DEATH_COUNT;

					DelCollision(g_enemy[i].colIndex);
					DelCollision(g_enemy[i].hitColIndex);

					PlaySound(SOUND_LABEL_SE_wana3);
				}
			}
		}




	}

	//クリア判定
	bool isAllKill = false;
	//すべてのエネミーが死んでいるか
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) {
			isAllKill = false;
			break;
		}
		else {
			isAllKill = true;
		}
	}
	if (isAllKill) {// すべて生きていなかったらクリアでリザルトに飛ばす
		SetIsClear(isAllKill);
		SetMode(MODE_RESULT);
	}
}
void DrawEnemy(void) {
	XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
	XMFLOAT4X4 camMtxView = GetCameraMtxView();

	SetAlphaTestEnable(true);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int Pindex = GetPlayerGameObjectIndex();
	XMFLOAT3 pPos = GetPosition(Pindex);

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) {

			if (g_enemy[i].state == ENEMY_DEATH) continue;

			float len = LengthXMFLOAT3(pPos, GetPosition(g_enemy[i].objIndex));

			if (len < BAR_SHOW_LEN) {

				//HPバーの下地の描画ーーーーーーーーーーーーーーーーーーーーーー
				MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer1, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);	// 長さをHPの残量に合わせる

				// 頂点バッファ設定
				stride = sizeof(VERTEX_3D);
				offset = 0;
				GetDeviceContext()->IASetVertexBuffers(0, 1, &g_enemy[i].vertexBuffer1, &stride, &offset);

				//色の変更
				g_enemy[i].material.Diffuse = BAR_COLOR_1;

				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

				XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);

				// ワールドマトリックスの初期化
				mtxWorld = XMMatrixIdentity();

				// ビューマトリックスを取得
				mtxView = XMLoadFloat4x4(&camMtxView);


				mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
				mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
				mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

				mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
				mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
				mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

				mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
				mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
				mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

				// 移動を反映
				pos.y += BAR_OFFSET_Y;
				mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
				mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

				// ワールドマトリックスの設定
				SetWorldMatrix(&mtxWorld);

				// マテリアル設定
				SetMaterial(g_enemy[i].material);

				// ポリゴンの描画
				GetDeviceContext()->Draw(4, 0);


				//HPバーの残量の描画ーーーーーーーーーーーーーーーーーーーーーー
				// 頂点バッファ生成
				MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer2, -BAR_SIZE_WIDTH + ((BAR_SIZE_WIDTH * (g_enemy[i].HP / 100.0f)) * 2), BAR_SIZE_HEIGHT);	// 長さをHPの残量に合わせる
				// 頂点バッファ設定
				stride = sizeof(VERTEX_3D);
				offset = 0;
				GetDeviceContext()->IASetVertexBuffers(0, 1, &g_enemy[i].vertexBuffer2, &stride, &offset);
				//色の変更
				g_enemy[i].material.Diffuse = BAR_COLOR_2;

				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

				pos = GetPosition(g_enemy[i].objIndex);

				// ワールドマトリックスの初期化
				mtxWorld = XMMatrixIdentity();

				// ビューマトリックスを取得
				mtxView = XMLoadFloat4x4(&camMtxView);

				mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
				mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
				mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

				mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
				mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
				mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

				mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
				mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
				mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

				// 移動を反映
				pos.y += BAR_OFFSET_Y;
				mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
				mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

				// ワールドマトリックスの設定
				SetWorldMatrix(&mtxWorld);

				// マテリアル設定
				SetMaterial(g_enemy[i].material);

				// ポリゴンの描画
				GetDeviceContext()->Draw(4, 0);

			}

		}
	}

	SetAlphaTestEnable(false);

}

void SetEnemy(XMFLOAT3 pos,XMFLOAT3 rot, XMFLOAT3 scl) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) continue;
		//エネミーを読み込むのはできてるからuseと座標回転大きさを書き換える
		SetPosition(g_enemy[i].objIndex, pos);
		SetRotation(g_enemy[i].objIndex, rot);
		SetScale(g_enemy[i].objIndex, scl);

		g_enemy[i].use = true;
		break;
	}
}

int GetAliveEnemy(void) {
	int ans = 0;
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) ans++;
	}
	return ans;
}


void LookPlayer(ENEMY* enemy) {
	if (enemy->state == ENEMY_DEATH) return;

	//エネミーの攻撃のクールダウンが終わっていたら新しく攻撃させる
	if (enemy->atkCount > 0) {
		if (CollisionBB(GetPosition(enemy->objIndex), LOOK_PLAYER, g_pPos, LOOK_PLAYER)) {
			enemy->isATK = true;
			enemy->state = ENEMY_ATK;
			enemy->atkCount = ATK_DELAY;
			XMFLOAT3 pos = GetPosition(enemy->objIndex);
			XMFLOAT3 rot = GetRotation(enemy->objIndex);

			enemy->rot.y = 0.01f;

		}
	}
	// クールダウンまち
	else {
		enemy->atkCount++;
	}
}


int GetEnemyIndex(int index) {
	if (g_enemy[index].use) {
		return g_enemy[index].objIndex;
	}
	return -1;
}

int GetEnemyHP(int index) {
	return g_enemy[index].HP;
}

void SetEnemyHP(int index, int hp) {
	g_enemy[index].HP = hp;
}


// 頂点情報の作成
HRESULT MakeVertexEnemyHpBar(ID3D11Buffer** vertexBuffer, float fWidth, float fHeight) {
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, vertexBuffer);

	// 頂点バッファに値をセットする
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(*vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// 頂点座標の設定

	vertex[0].Position = XMFLOAT3(-BAR_SIZE_WIDTH / 2, 0, 0.0f);
	vertex[1].Position = XMFLOAT3(fWidth / 2, 0, 0.0f);
	vertex[2].Position = XMFLOAT3(-BAR_SIZE_WIDTH / 2, -fHeight, 0.0f);
	vertex[3].Position = XMFLOAT3(fWidth / 2, -fHeight, 0.0f);

	// 拡散光の設定
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	GetDeviceContext()->Unmap(*vertexBuffer, 0);

	return S_OK;
}