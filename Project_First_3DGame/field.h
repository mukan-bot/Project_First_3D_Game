#pragma once
#include "main.h"
#include "model.h"


struct SET_OBJECT {
	int gameObjectIndex;
	int gameModelIndex;
	int collisonIndex;
	int fieldCollisonIndex;
};


HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

// フィールドオブジェクトのGameObjectindexを所得
SET_OBJECT* GetFieldObject(int* objectCount);