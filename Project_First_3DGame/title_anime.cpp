#include "main.h"
#include "title_anime.h"


#define MODEL_PATH	("./data/MODEL/Skull/skull.obj")
#define MODEL_PARTS_PATH	("./data/MODEL/Skull/jaw.obj")

#define MAX	(20)

struct TITLE_ANIME_OBJ
{
	int objIndex;
	int ModelIndex;
	bool use;
};

TITLE_ANIME_OBJ g_obj[MAX];

void InitTitleAinme(void) {
	for (int i = 0; i < MAX; i++) {
		g_obj[i].objIndex = -1;
		g_obj[i].ModelIndex = -1;
		g_obj[i].use = false;
	}

}
void UninitTitleAnime(void) {

}
void UpdateTitleAnime(void) {

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