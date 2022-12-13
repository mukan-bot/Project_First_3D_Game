//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"

#include "GameObject.h"
#define MAX_OBJECT	(256)	//とりあえず何も考えず２５６にしておく


struct GAME_OBJECT
{
	XMFLOAT3 position;		//座標
	XMFLOAT3 rotation;		//回転
	XMFLOAT3 scale;			//大きさ
	bool use;				//使われているか
	int parentIndex;		//親のインデックス番号（親なら-1）
};


GAME_OBJECT g_gameObject[MAX_OBJECT];





void UpdateGameObject(void) {
	for (int i = 0; i < MAX_OBJECT; i++) {
		if (!g_gameObject[i].use) continue;

		if (g_gameObject[i].parentIndex == -1) continue;

		g_gameObject[i].position = AddXMFLOAT3(g_gameObject[i].position, g_gameObject[g_gameObject[i].parentIndex].position);
		g_gameObject[i].rotation = AddXMFLOAT3(g_gameObject[i].rotation, g_gameObject[g_gameObject[i].parentIndex].rotation);
		g_gameObject[i].scale = AddXMFLOAT3(g_gameObject[i].scale, g_gameObject[g_gameObject[i].parentIndex].scale);
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
	if (ans == -1)OutputDebug("SetGameObjectで-1が返されました。\n");
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

	//一周回ったら値を０にする
	if (rotation.x >= XM_PI * 2.0f) {
		int temp = rotation.x - XM_PI * 2.0f;
		rotation.x = temp;
	}
	else if (-rotation.x >= XM_PI * 2.0f) {
		int temp = -rotation.x - XM_PI * 2.0f;
		rotation.x = temp;
	}
	if (rotation.y >= XM_PI * 2.0f) {
		int temp = rotation.y - XM_PI * 2.0f;
		rotation.y = temp;
	}
	else if (-rotation.y >= XM_PI * 2.0f) {
		int temp = -rotation.y - XM_PI * 2.0f;
		rotation.y = temp;
	}
	if (rotation.z >= XM_PI * 2.0f) {
		int temp = rotation.z - XM_PI * 2.0f;
		rotation.z = temp;
	}
	else if (-rotation.z >= XM_PI * 2.0f) {
		int temp = -rotation.z - XM_PI * 2.0f;
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
	g_gameObject[index].scale = XMFLOAT3(0.0f, 0.0f, 0.0f);
}


XMFLOAT3 GetPosition(int index) {
	return g_gameObject[index].position;
}
XMFLOAT3 GetRotation(int index) {
	return g_gameObject[index].rotation;
}
XMFLOAT3 GetScale(int index) {
	return g_gameObject[index].scale;
}
int GetGameObjectParent(int index) {
	return g_gameObject[index].parentIndex;
}
