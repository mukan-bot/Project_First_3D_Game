//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"

#include "GameObject.h"
#define MAX_OBJECT	(1024)	//�Ƃ肠���������l�����Q�T�U�ɂ��Ă���


struct GAME_OBJECT
{
	XMFLOAT3 position;		//���W
	XMFLOAT3 rotation;		//��]
	XMFLOAT3 scale;			//�傫��
	bool use = false;				//�g���Ă��邩
	int parentIndex;		//�e�̃C���f�b�N�X�ԍ��i�e�Ȃ�-1�j
};


GAME_OBJECT g_gameObject[MAX_OBJECT];


void InitGameObject(void) {
	for (int i = 0; i < MAX_OBJECT; i++) {
		g_gameObject[i].use = false;
	}
}


void UpdateGameObject(void) {
	for (int i = 0; i < MAX_OBJECT; i++) {
		if (!g_gameObject[i].use) continue;

		if (g_gameObject[i].parentIndex == -1) continue;

		//�e�������Ă�����q���������B
		if (!g_gameObject[g_gameObject[i].parentIndex].use) {
			g_gameObject[i].use = false;
			continue;
		}
	}
}








int SetGameObject(void) {
	int ans = -1;
	for (int i = 0; i < MAX_OBJECT; i++){
		if (g_gameObject[i].use) continue;
		
		g_gameObject[i].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_gameObject[i].rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_gameObject[i].scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_gameObject[i].use = true;
		g_gameObject[i].parentIndex = -1;

		ans = i;
		break;
	}
#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetGameObject��-1���Ԃ���܂����B\n");
	}
#endif // _DEBUG

	return ans;
}

void DelGameObject(int index) {
	g_gameObject[index].use = false;
	g_gameObject[index].parentIndex = -1;	
}



void SetPosition(int index, XMFLOAT3 position) {
	g_gameObject[index].position = position;
}
void SetRotation(int index, XMFLOAT3 rotation) {

	//����������l���O�ɂ���
	if (rotation.x >= XM_PI * 2.0f) {
		float temp= rotation.x - XM_PI * 2.0f;
		rotation.x = temp;
	}
	else if (-rotation.x >= XM_PI * 2.0f) {
		float temp = -rotation.x - XM_PI * 2.0f;
		rotation.x = temp;
	}
	if (rotation.y >= XM_PI * 2.0f) {
		float temp= rotation.y - XM_PI * 2.0f;
		rotation.y = temp;
	}
	else if (-rotation.y >= XM_PI * 2.0f) {
		float temp= -rotation.y - XM_PI * 2.0f;
		rotation.y = temp;
	}
	if (rotation.z >= XM_PI * 2.0f) {
		float temp= rotation.z - XM_PI * 2.0f;
		rotation.z = temp;
	}
	else if (-rotation.z >= XM_PI * 2.0f) {
		float temp= -rotation.z - XM_PI * 2.0f;
		rotation.z = temp;
	}
	g_gameObject[index].rotation = rotation;
}
void SetScale(int index, XMFLOAT3 scale) {
	g_gameObject[index].scale = scale;
}
void SetGameObjectParent(int index, int parentIndex) {
	g_gameObject[index].parentIndex = parentIndex;
}
void SetGameObjectZERO(int index) {
	g_gameObject[index].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_gameObject[index].rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_gameObject[index].scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}


XMFLOAT3 GetPosition(int index) {
	XMFLOAT3 ans = g_gameObject[index].position;
	// �y�A�����g���ݒ肳��Ă����炻��𑫂����l��Ԃ�
	if (g_gameObject[index].parentIndex != -1) {
		ans = AddXMFLOAT3(ans, g_gameObject[g_gameObject[index].parentIndex].position);
	}
	return ans;
}
XMFLOAT3 GetRotation(int index) {
	XMFLOAT3 ans = g_gameObject[index].rotation;
	// �y�A�����g���ݒ肳��Ă����炻��𑫂����l��Ԃ�
	if (g_gameObject[index].parentIndex != -1) {
		ans = AddXMFLOAT3(ans, g_gameObject[g_gameObject[index].parentIndex].rotation);
	}
	return ans;
}
XMFLOAT3 GetScale(int index) {
	XMFLOAT3 ans = g_gameObject[index].scale;
	// �y�A�����g���ݒ肳��Ă����炻��𑫂����l��Ԃ�
	if (g_gameObject[index].parentIndex != -1) {
		ans = MulXMFLOAT3(ans, g_gameObject[g_gameObject[index].parentIndex].scale);
	}
	return ans;
}
int GetGameObjectParent(int index) {
	return g_gameObject[index].parentIndex;
}
bool GetGameObjectUse(int index) {
	return g_gameObject[index].use;
}