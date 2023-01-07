#include "field.h"

#include "model.h"

#include "GameObject.h"
#include "GameModel.h"

#include "collision.h"
#include "player.h"
#include "enemy.h"


#define FIELD_MODEL_MAX	(6)
#define CSV_FILE_PATH	"./object_properties.csv"
#define SET_OBJECT_MAX (256)

float CharToFloat(char* text);



static char* g_modelPath[FIELD_MODEL_MAX][3]{
	//パス、名前、collision配置1なら配置
	{"./data/MODEL/field/field.obj","ita","0"},
	{"./data/MODEL/field/test.obj" ,"Monkey","0"},
	{"./data/MODEL/field/cone.obj" ,"Cone","0"},
	{"./data/MODEL/field/Ground001.obj" ,"Ground001","1"},
	{"./data/MODEL/field/Ground002.obj" ,"Ground002","1"},
	{"./data/MODEL/field/Ground003.obj" ,"Ground003","2"},

};

static int g_elementCount;

static SET_OBJECT  g_setObject[SET_OBJECT_MAX];

XMFLOAT3 g_setObjectPos[SET_OBJECT_MAX];


HRESULT InitField(void) {

	for (int i = 0; i < SET_OBJECT_MAX; i++) {
		g_setObject[i].collisonIndex = -1;
		g_setObject[i].fieldCollisonIndex = -1;
		g_setObject[i].gameModelIndex = -1;
		g_setObject[i].gameObjectIndex = -1;
	}


	FILE* fp;
	g_elementCount = -1;
	char name[256];
	XMFLOAT3 pos, rot, scl;
	fopen_s(&fp, CSV_FILE_PATH, "r");
	if (fp != NULL) {
		//while (fscanf_s(fp, "%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", name, _countof(name), &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &scl.x, &scl.y, &scl.z) != EOF)
		while (fscanf_s(fp, "%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f", name, _countof(name), &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &scl.x, &scl.y, &scl.z) != EOF)
		{
			g_elementCount++;
		}
		fclose(fp);
	}



	for (int i = 0; i < g_elementCount; i++) {
		fopen_s(&fp, CSV_FILE_PATH, "r");	//毎回ファイルを開くのは効率悪いかも
		LEVEL_ELEMENT ans;
		GetLevel_Csv(fp, i, &ans);


		//オブジェクトの名前が連番になるので連番部分の削除
		int nameEnd = 0;
		while (ans.name[nameEnd]!='.'){
			if (ans.name[nameEnd] == '\0')break;
			nameEnd++;
		}
		ans.name[nameEnd] = '\0';
		OutputDebug("%s\n", ans.name);

		//collisionだったらcollisionを配置する
		if (strcmp(ans.name, "collisionBB") == 0) {
			g_setObject[i].collisonIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
			int index = GetColObjectIndex(g_setObject[i].collisonIndex);
			SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));
			//SetRotation(index, ans.rot);
			SetScale(index, ans.scl);
			continue;
		}
		//collisionだったらcollisionを配置する
		if (strcmp(ans.name, "collisionBC") == 0) {
			g_setObject[i].collisonIndex = SetCollision(LAYER_OBSTACLE, TYPE_BC);
			int index = GetColObjectIndex(g_setObject[i].collisonIndex);
			SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));
			SetRotation(index, ans.rot);
			SetScale(index, ans.scl);
			continue;
		}

		//Playerだったらそこにプレイヤーを配置する
		if (strcmp(ans.name, "Player") == 0) {
			int objIndex = GetPlayerGameObjectIndex();
			int colIndex = GetPlayerColObjectIndex();
			int index = GetColObjectIndex(colIndex);
			SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));
			ans.rot.x += XM_PI;	//なんか反対に向いてしまうので修正（blenderの座標軸よくわからん）
			SetRotation(objIndex, ans.rot);

			SetScale(index, ans.scl);

			//初期のめり込みを解消する
			while (GetColAnsUpdate(colIndex))
			{
				XMFLOAT3 pos = GetPosition(index);
				pos.y += 0.01f;
				SetPosition(index, pos);
			}
			SetPosition(objIndex, GetPosition(index));
			continue;
		}

		//ENEMYだったらENEMYを配置する
		if (strcmp(ans.name, "Enemy") == 0) {
			SetEnemy(MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)),ans.rot, ans.scl);
		}

		int index = g_setObject[i].gameObjectIndex = SetGameObject();
		SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));	//座標がずれるから調節
		SetRotation(index, ans.rot);
		SetScale(index, ans.scl);

		//その他のオブジェクトを配置
		for (int j = 0; j < FIELD_MODEL_MAX; j++) {
			if (strcmp(ans.name, g_modelPath[j][1])==0) {
				g_setObject[i].gameModelIndex = SetGameModel(g_modelPath[j][0], index, 0, CULL_MODE_BACK);
				if (strcmp("1", g_modelPath[j][2]) == 0) {	//collisionを配置するオブジェクトなら配置する
					g_setObject[i].collisonIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
					int index = GetColObjectIndex(g_setObject[i].collisonIndex);
					SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));
					SetScale(index, ans.scl);

					g_setObject[i].fieldCollisonIndex = SetCollision(LAYER_FIELD, TYPE_BB);
					index = GetColObjectIndex(g_setObject[i].fieldCollisonIndex);
					SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));
					SetScale(index, ans.scl);
				}
				break;
			}
		}
		fclose(fp);
	}
	if (fp != NULL) {
		fclose(fp);
	}

	for (int i = 0; i < g_elementCount; i++) {
		g_setObjectPos[i] = GetPosition(g_setObject[i].gameObjectIndex);
	}

	return S_OK;
}

void UninitField(void) {
	for (int i = 0; i < g_elementCount; i++) {
		DelGameModel(g_setObject[i].gameModelIndex);
	}
}

void UpdateField(void) {
	for (int i = 0; i < g_elementCount; i++) {
		if (ComparisonXMFLOAT3(g_setObjectPos[i], GetPosition(g_setObject[i].gameObjectIndex))) {
			OutputDebug("フィールドオブジェクトの座標が移動されました\n");
		}
	}
}

void DrawField(void) {
}


float CharToFloat(char* text) {
	float ans = 0.0f;
	if (text != NULL) {
		char* end;
		ans = strtof(text, &end);
	}
	return ans;
}



SET_OBJECT* GetFieldObject(int* objectCount) {
	objectCount[0] = g_elementCount;
	return g_setObject;
}

