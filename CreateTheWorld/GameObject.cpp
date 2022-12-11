#include "main.h"

#include "GameObject.h"
#define MAX_OBJECT	(256)	//Ç∆ÇËÇ†Ç¶Ç∏âΩÇ‡çlÇ¶Ç∏ÇQÇTÇUÇ…ÇµÇƒÇ®Ç≠

GAME_OBJECT g_gameObject[MAX_OBJECT];


int SetGameObject(void) {
	int ans = -1;
	for (int i = 0; i < MAX_OBJECT; i++){
		if (g_gameObject[i].use) continue;
		
		g_gameObject[i].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_gameObject[i].rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_gameObject[i].scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_gameObject[i].use = true;
		
		ans = i;
		break;
	}
#ifdef _DEBUG
	if (ans == -1)OutputDebug("SetGameObjectÇ≈-1Ç™ï‘Ç≥ÇÍÇ‹ÇµÇΩÅB\n");
#endif // _DEBUG

	return ans;
}

void DelGameObject(int index) {
	g_gameObject[index].use = false;
}



void SetPosition(int index, XMFLOAT3 position) {
	g_gameObject[index].position = position;
}
void SetRotation(int index, XMFLOAT3 rotation) {
	g_gameObject[index].rotation = rotation;
}
void SetScale(int index, XMFLOAT3 scale) {
	g_gameObject[index].scale = scale;
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
