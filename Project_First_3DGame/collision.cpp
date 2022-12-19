//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"
#include "collision.h"

#define MAX_OBJECT	(256)	//Ç∆ÇËÇ†Ç¶Ç∏âΩÇ‡çlÇ¶Ç∏ÇQÇTÇUÇ…ÇµÇƒÇ®Ç≠

COLLISION g_collision[MAX_OBJECT];

int SetCollision(int gaemObjectIndex, XMFLOAT3 size, COLLISION_TYPE type) {
	int ans = -1;
	for (int i = 0; i < MAX_OBJECT; i++){
		if (g_collision[i].use) continue;
		
		g_collision[i].gameObjectIndex = gaemObjectIndex;
		g_collision[i].size = size;
		g_collision[i].type = type;
		g_collision[i].use = true;
		ans = i;
		break;
	}
	return ans;
}

