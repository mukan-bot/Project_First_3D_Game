#include "field.h"

#include "model.h"

#include "GameObject.h"
#include "GameModel.h"

#include "collision.h"


#define FIELD_MODEL_MAX	(3)
#define CSV_FILE_PATH	"./object_properties.csv"
#define SET_OBJECT_MAX (256)

float CharToFloat(char* text);



struct SET_OBJECT {
	int gameObjectIndex;
	int gameModelIndex;
	int collisonIndex;
};



static char* g_modelPath[FIELD_MODEL_MAX][2]{
	{"./data/MODEL/field.obj","ïΩñ "},
	{"./data/MODEL/test.obj" ,"ÉÇÉìÉLÅ["},
	{"./data/MODEL/cone.obj" ,"Cone"},
};

static int g_setModelNo = 0;

static SET_OBJECT  g_setObject[SET_OBJECT_MAX];


HRESULT InitField(void) {
	int i = 1;
	FILE* fp;
	fopen_s(&fp, CSV_FILE_PATH, "r");
	if (fp != NULL) {

		while (GetElement(fp, i, 0) != NULL) {
			g_setObject[i].gameObjectIndex = SetGameObject();
			XMFLOAT3 pos;
			XMFLOAT3 rot;
			XMFLOAT3 scl;


			char* name = GetElement(fp, i, 0);

			for (int j = 0; j < FIELD_MODEL_MAX; j++) {
				if (strcmp(name, g_modelPath[j][1]) == 0) {
					SetGameModel(g_modelPath[j][0], g_setObject[i].gameObjectIndex, 0, CULL_MODE_NONE);
				}
			}

			pos.x = CharToFloat(GetElement(fp, 1, i));


			
			/*
			pos.y = strtof(GetElement(fp, i, 2), &end);
			pos.z = strtof(GetElement(fp, i, 3), &end);
			rot.x = strtof(GetElement(fp, i, 4), &end);
			rot.y = strtof(GetElement(fp, i, 5), &end);
			rot.z = strtof(GetElement(fp, i, 6), &end);
			scl.x = strtof(GetElement(fp, i, 7), &end);
			scl.y = strtof(GetElement(fp, i, 8), &end);
			scl.z = strtof(GetElement(fp, i, 9), &end);*/


			//SetPosition(g_setObject[i].gameObjectIndex, pos);
			//SetRotation(g_setObject[i].gameObjectIndex, rot);
			//SetScale(g_setObject[i].gameObjectIndex, scl);

			i++;
		}
	}
	if (fp != NULL) {
		fclose(fp);
	}
	g_setModelNo = i;

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