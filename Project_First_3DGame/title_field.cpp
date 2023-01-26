#include "title_field.h"

#include "model.h"

#include "GameObject.h"
#include "GameModel.h"

#include "title_anime.h"


#define FIELD_MODEL_MAX	(6)
#define CSV_FILE_PATH	"./title_field.csv"
#define SET_OBJECT_MAX (256)

// �����񂩂�float�֕ϊ�����
float CharToFloat(char* text);



static char* g_modelPath[FIELD_MODEL_MAX][3]{
	//�p�X�A���O�Acollision�z�u1�Ȃ�z�u
	{"./data/MODEL/field/field.obj","ita","0"},
	{"./data/MODEL/field/test.obj" ,"Monkey","0"},
	{"./data/MODEL/field/cone.obj" ,"Cone","0"},
	{"./data/MODEL/field/Ground001.obj" ,"Ground001","1"},
	{"./data/MODEL/field/Ground002.obj" ,"Ground002","1"},
	{"./data/MODEL/field/Ground003.obj" ,"Ground003","1"},

};

static int g_elementCount;	//�����邩

static SET_OBJECT  g_setObject[SET_OBJECT_MAX];	//�ݒu����I�u�W�F�N�g

static XMFLOAT3 g_setObjectPos[SET_OBJECT_MAX];


HRESULT InitTitleField(void) {

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
		//�Ō�܂Ń��[�v�œǂݍ���
		while (fscanf_s(fp, "%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f", name, _countof(name), &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &scl.x, &scl.y, &scl.z) != EOF)
		{
			g_elementCount++;	//�����邩
		}
		fclose(fp);
	}



	for (int i = 0; i < g_elementCount; i++) {
		fopen_s(&fp, CSV_FILE_PATH, "r");	//����t�@�C�����J���̂͌�����������
		LEVEL_ELEMENT ans;
		GetLevel_Csv(fp, i, &ans);


		//�I�u�W�F�N�g�̖��O���A�ԂɂȂ�̂ŘA�ԕ����̍폜
		int nameEnd = 0;
		while (ans.name[nameEnd] != '.') {
			if (ans.name[nameEnd] == '\0')break;
			nameEnd++;
		}
		ans.name[nameEnd] = '\0';
		OutputDebug("%s\n", ans.name);


		// �z�u����(skull)
		if (strcmp(ans.name, "ANIME_OBJ") == 0) {
			SetTitleAnimeObj(MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)), ans.rot, ans.scl);
			continue;
		}

		int index = g_setObject[i].gameObjectIndex = SetGameObject();
		//SetPosition(index, ans.pos);
		SetPosition(index, MulXMFLOAT3(ans.pos, SetXMFLOAT3(10.0f)));	//���W������邩�璲��
		SetRotation(index, MulXMFLOAT3(ans.rot, SetXMFLOAT3(-1.0f)));
		SetScale(index, ans.scl);

		//���̑��̃I�u�W�F�N�g��z�u
		for (int j = 0; j < FIELD_MODEL_MAX; j++) {
			if (strcmp(ans.name, g_modelPath[j][1]) == 0) {
				g_setObject[i].gameModelIndex = SetGameModel(g_modelPath[j][0], index, 0, CULL_MODE_BACK);

				break;
			}
		}
		fclose(fp);
	}
	if (fp != NULL) {
		fclose(fp);
	}

	// Position��ۑ����Ă���
	for (int i = 0; i < g_elementCount; i++) {
		g_setObjectPos[i] = GetPosition(g_setObject[i].gameObjectIndex);
	}

	return S_OK;
}

void UninitTitleField(void) {
	for (int i = 0; i < g_elementCount; i++) {
		DelGameModel(g_setObject[i].gameModelIndex);
	}
}

void UpdateTitleField(void) {

}

void DrawTitleField(void) {
}





SET_OBJECT* GetTitleFieldObject(int* objectCount) {
	objectCount[0] = g_elementCount;
	return g_setObject;
}