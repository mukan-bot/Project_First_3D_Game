#include "field.h"

#include "model.h"

#include "GameObject.h"
#include "GameModel.h"

#include "collision.h"


#define FIELD_MODEL_MAX	(5)
#define CSV_FILE_PATH	"./object_properties.csv"
#define SET_OBJECT_MAX (256)

float CharToFloat(char* text);



static char* g_modelPath[FIELD_MODEL_MAX][2]{
	{"./data/MODEL/field.obj","ita"},
	{"./data/MODEL/test.obj" ,"Monkey"},
	{"./data/MODEL/cone.obj" ,"Cone"},
	{"./data/MODEL/Ground001.obj" ,"Ground001"},
	{"./data/MODEL/Ground002.obj" ,"Ground002"},

};

static int g_elementCount;

static SET_OBJECT  g_setObject[SET_OBJECT_MAX];


HRESULT InitField(void) {

	for (int i = 0; i < SET_OBJECT_MAX; i++) {
		g_setObject[i].collisonIndex = -1;
		g_setObject[i].gameModelIndex = -1;
		g_setObject[i].gameObjectIndex = -1;
	}


	FILE* fp;
	g_elementCount = -1;
	char name[256];
	XMFLOAT3 pos, rot, scl;
	fopen_s(&fp, CSV_FILE_PATH, "r");
	if (fp != NULL) {
		while (fscanf_s(fp, "%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", name, _countof(name), &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &scl.x, &scl.y, &scl.z) != EOF)
		{
			g_elementCount++;
		}
		fclose(fp);
	}



	for (int i = 0; i < g_elementCount; i++) {
		fopen_s(&fp, CSV_FILE_PATH, "r");
		LEVEL_ELEMENT ans;
		GetLevel_Csv(fp, i, &ans);
		//OutputDebug("%d\n", i);
		//if (&ans == NULL) continue;


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

		int index = g_setObject[i].gameObjectIndex = SetGameObject();
		SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));	//座標がずれるから調節
		SetRotation(index, ans.rot);
		SetScale(index, ans.scl);

		for (int j = 0; j < FIELD_MODEL_MAX; j++) {
			if (strcmp(ans.name, g_modelPath[j][1])==0) {
				g_setObject[i].gameModelIndex = SetGameModel(g_modelPath[j][0], index, 0, CULL_MODE_NONE);
				break;
			}
		}
		fclose(fp);
	}
	if (fp != NULL) {
		fclose(fp);
	}

	return S_OK;
}
void UninitField(void) {

}
void UpdateField(void) {


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