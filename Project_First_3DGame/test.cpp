//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "test.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_TEST		"data/MODEL/Kirby_Body.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST_LEG_L	"data/MODEL/Kirby_Leg_L.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST_LEG_R	"data/MODEL/Kirby_Leg_R.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST_ARM_L	"data/MODEL/Kirby_Arm_L.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST_ARM_R	"data/MODEL/Kirby_Arm_R.obj"			// �ǂݍ��ރ��f����

#define TEST_OFFSET	(5.0f)
#define TEST_PARTS	(4)

static int g_objIndex;
static int g_mdlIndex;

static int g_partsObjIndex[TEST_PARTS];
static int g_partsMdlIndex[TEST_PARTS];







//=============================================================================
// ����������
//=============================================================================
HRESULT InitTest(void)
{
	//�{�̂̏�����
	g_objIndex = SetGameObject();
	g_mdlIndex = SetGameModel(MODEL_TEST, g_objIndex, 1, CULL_MODE_NONE);
	SetPosition(g_objIndex, XMFLOAT3(0.0f, TEST_OFFSET, 0.0f));
	SetScale(g_objIndex, XMFLOAT3(0.01f, 0.01f, 0.01f));

	//�p�[�c�̏�����

	int i = 0;	//MEMO:�R�s�y���Ղ��悤�ɁA�z��ԍ���i�ɂ��Ă������߁B
	g_partsObjIndex[i] = SetGameObject();
	g_partsMdlIndex[i] = SetGameModel(MODEL_TEST_LEG_L, g_partsObjIndex[i], 1, CULL_MODE_NONE);
	SetGameObjectParent(g_partsObjIndex[i], g_objIndex);
	i++;
	g_partsObjIndex[i] = SetGameObject();
	g_partsMdlIndex[i] = SetGameModel(MODEL_TEST_LEG_R, g_partsObjIndex[i], 1, CULL_MODE_NONE);
	SetGameObjectParent(g_partsObjIndex[i], g_objIndex);
	i++;
	g_partsObjIndex[i] = SetGameObject();
	g_partsMdlIndex[i] = SetGameModel(MODEL_TEST_ARM_L, g_partsObjIndex[i], 1, CULL_MODE_NONE);
	SetGameObjectParent(g_partsObjIndex[i], g_objIndex);
	i++;
	g_partsObjIndex[i] = SetGameObject();
	g_partsMdlIndex[i] = SetGameModel(MODEL_TEST_ARM_R, g_partsObjIndex[i], 1, CULL_MODE_NONE);
	SetGameObjectParent(g_partsObjIndex[i], g_objIndex);


	
	for (int i = 0; i < TEST_PARTS; i++) {
		SetGameObjectZERO(g_partsObjIndex[i]);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTest(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTest(void) {
	for (int i = 0; i < TEST_PARTS; i++) {
		SetGameObjectZERO(g_partsObjIndex[i]);
	}

	XMFLOAT3 pos = GetPosition(g_objIndex);
	XMFLOAT3 rot = GetRotation(g_objIndex);
	XMFLOAT3 scl = GetScale(g_objIndex);
	if (GetInputPress(MOVE_FRONT)) {
		pos.z += 0.01f;
		SetPosition(g_objIndex, pos);
	}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTest(void)
{

}

