#include "main.h"
#include "title_anime.h"


#define MODEL_PATH	("./data/MODEL/Skull/skull.obj")
#define MODEL_PARTS_PATH	("./data/MODEL/Skull/jaw.obj")

#define MAX	(20)

#define COUNT_MAX (240)

#define ROTATION_SPEED	(0.50f)	//デグリー角度で１Fの最大速度

enum STATE
{
	CHANGE,		// どの行動をするか決める 
	ROTATION,		// 回転
	HAHA,			// 笑い（口パカパカ）
	DISSOLVE,		// 消え隠れ 
	STOP,			// 何もしない
};


struct TITLE_ANIME_OBJ
{
	int objIndex;
	int ModelIndex;
	int count;
	STATE state;
	XMFLOAT3 pos;	// 初期座標
	XMFLOAT3 rot;	// 初期回転量
	XMFLOAT3 scl;	// 初期スケール

	XMFLOAT3 temp;	//各種アニメーションに使う為の変数

	bool use;
};

TITLE_ANIME_OBJ g_obj[MAX];

void InitTitleAinme(void) {
	for (int i = 0; i < MAX; i++) {
		g_obj[i].objIndex = -1;
		g_obj[i].ModelIndex = -1;
		g_obj[i].count = 0;
		g_obj[i].state = CHANGE;
		g_obj[i].temp = SetXMFLOAT3(0.0f);
		g_obj[i].use = false;
	}
}
void UninitTitleAnime(void) {
	// タイトルが終了する時Modelを開放するからここでは何もしない
}
void UpdateTitleAnime(void) {
	for (int i = 0; i < MAX; i++) {
		if (!g_obj[i].use) continue;

		if (GetGameObjectParent(g_obj[i].objIndex) != -1) continue;


		switch (g_obj[i].state)
		{
		case CHANGE:
		{
			g_obj[i].count = 0;
			// 一旦すべてリセット
			SetPosition(g_obj[i].objIndex, g_obj[i].pos);
			SetRotation(g_obj[i].objIndex, g_obj[i].rot);
			SetScale(g_obj[i].objIndex, g_obj[i].scl);

			int prob = rand() % 10;
			switch ((STATE)prob)
			{
			case ROTATION:
				g_obj[i].state = ROTATION;
				break;
			case HAHA:
				g_obj[i].state = HAHA;
				break;
			case DISSOLVE:
				g_obj[i].state = DISSOLVE;
				break;
			case STOP:
			default:
				g_obj[i].state = STOP;
				break;
			}
			g_obj[i].state = HAHA;
		}

			break;
		case ROTATION:
			if (g_obj[i].count < COUNT_MAX) {
				XMFLOAT3 rot = GetRotation(g_obj[i].objIndex);
				if (g_obj[i].count < COUNT_MAX / 2) {
					g_obj[i].temp.y += DegToRad(ROTATION_SPEED);
				}
				else {
					g_obj[i].temp.y -= DegToRad(ROTATION_SPEED);
				}
				rot = AddXMFLOAT3(rot, g_obj[i].temp);
				SetRotation(g_obj[i].objIndex, rot);
				g_obj[i].count++;
			}
			else {
				g_obj[i].state = CHANGE;
			}
			break;
		case HAHA:
		{
			int* childIndex = GetGameObjectChild(g_obj[i].objIndex);
			XMFLOAT3 rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
			if (g_obj[i].count < COUNT_MAX) {
				if (g_obj[i].count % (COUNT_MAX / 2) == 0) {
					rot.x = 0.5f;
					OutputDebug("\n");
				}
				if (g_obj[i].count % (COUNT_MAX / 4) == 0) {
					rot.x = 0.0f;
					OutputDebug("t");
				}
			}
			else {
				rot = SetXMFLOAT3(0.0f);
				g_obj[i].state = CHANGE;

			}
			SetRotation(childIndex[0], rot);
			g_obj[i].count++;
		}
			break;
		case DISSOLVE:
		{
			float dissolve = GetGameModelDissolve(g_obj[i].ModelIndex);
			int* childIndex = GetGameObjectChild(g_obj[i].objIndex);
			if (g_obj[i].count < COUNT_MAX * 2) {	//消えて少し待ってから戻すためカウントより多くする
				if (g_obj[i].count < COUNT_MAX / 2) {
					dissolve -= 1.0f / COUNT_MAX * 2;
					SetGameModelDissolve(g_obj[i].ModelIndex, dissolve);
					SetGameModelDissolve(childIndex[0], dissolve);
				}
			}
			else if (g_obj[i].count < (COUNT_MAX * 2) + COUNT_MAX / 2) {	// 時間が来たら戻す
				dissolve += 1.0f / COUNT_MAX * 2;
				SetGameModelDissolve(g_obj[i].ModelIndex, dissolve);
				SetGameModelDissolve(childIndex[0], dissolve);
			}
			else {
				g_obj[i].state = CHANGE;
			}
			g_obj[i].count++;
		}
			break;
		case STOP:
			if (g_obj[i].count < rand()%COUNT_MAX) {	// 待ち時間を不均一かする
				g_obj[i].count++;
			}
			else {
				g_obj[i].state = CHANGE;

			}
			break;
		default:
			break;
		}


	}
}
void DrawTitleAnime(void) {

}


void SetTitleAnimeObj(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl) {
	rot.y = -rot.y;
	int parentIndex = -1;
	for (int i = 0; i < MAX; i++) {
		if (g_obj[i].use) continue;

		parentIndex = g_obj[i].objIndex = SetGameObject();
		SetPosition(g_obj[i].objIndex, pos);
		SetRotation(g_obj[i].objIndex, rot);
		SetScale(g_obj[i].objIndex, scl);

		g_obj[i].ModelIndex = SetGameModel(MODEL_PATH, g_obj[i].objIndex, 0, CULL_MODE_BACK);

		g_obj[i].pos = pos;
		g_obj[i].rot = rot;
		g_obj[i].scl = scl;

		g_obj[i].use = true;
		break;
	}

	for (int i = 0; i < MAX; i++) {
		if (g_obj[i].use) continue;

		int index = g_obj[i].objIndex = SetGameObject();
		SetGameObjectParent(index, parentIndex);

		g_obj[i].ModelIndex = SetGameModel(MODEL_PARTS_PATH, index, 0, CULL_MODE_BACK);

		g_obj[i].use = true;
		break;

	}

}