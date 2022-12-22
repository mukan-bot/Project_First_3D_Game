#include "field.h"

#include "GameObject.h"
#include "GameModel.h"

#include "collision.h"

#define FIELD_MODEL ("./data/MODEL/field.obj")

static int g_objIndex;
static int g_mdlIndex;

static int g_colIndex;

HRESULT InitField(void) {
	g_objIndex = SetGameObject();
	SetScale(g_objIndex, XMFLOAT3(1.0f, 1.0f, 1.0f));
	g_mdlIndex = SetGameModel(FIELD_MODEL, g_objIndex, 0, CULL_MODE_NONE);

	g_colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
	int colObjIndex = GetColObjectIndex(g_colIndex);
	SetPosition(colObjIndex, GetPosition(g_objIndex));
	SetScale(colObjIndex, XMFLOAT3(1.0, 0.001, 1.0));
	

	return S_OK;
}
void UninitField(void) {

}
void UpdateField(void) {


}
void DrawField(void) {

}