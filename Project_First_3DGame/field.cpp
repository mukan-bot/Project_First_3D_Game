#include "field.h"

#include "model.h"

#include "GameObject.h"
#include "GameModel.h"

#include "collision.h"


#define FIELD_MODEL_MAX	(3)

static char* g_modelPath[FIELD_MODEL_MAX][2]{
	{"./data/MODEL/field.obj","ïΩñ "},
	{"./data/MODEL/test.obj" ,"ÉÇÉìÉLÅ["},
	{"./data/MODEL/cone.obj" ,"Cone"},
};

static SET_MODEL g_setModel[FIELD_MODEL_MAX];


HRESULT InitField(void) {
	for (int i = 0; i < FIELD_MODEL_MAX; i++) {
		LoadModel(g_modelPath[i][0], &g_setModel[i].model);
		g_setModel[i].name = g_modelPath[i][1];
	}
	

	return S_OK;
}
void UninitField(void) {

}
void UpdateField(void) {


}
void DrawField(void) {

}