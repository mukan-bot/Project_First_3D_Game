#include "field.h"

#include "GameObject.h"
#include "GameModel.h"

#define FIELD_MODEL ("./data/MODEL/field.obj")

int g_objIndex;
int g_mdlIndex;

HRESULT InitField(void) {
	g_objIndex = SetGameObject();
	SetScale(g_objIndex, XMFLOAT3(2.0f, 2.0f, 2.0f));
	g_mdlIndex = SetGameModel(FIELD_MODEL, g_objIndex, 0, CULL_MODE_NONE);
	return S_OK;
}
void UninitField(void) {

}
void UpdateField(void) {

}
void DrawField(void) {

}