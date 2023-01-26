#pragma once
#include "main.h"
#include "model.h"


struct SET_OBJECT {
	int gameObjectIndex;
	int gameModelIndex;
	int collisonIndex;
	int fieldCollisonIndex;
};


HRESULT InitTitleField(void);
void UninitTitleField(void);
void UpdateTitleField(void);
void DrawTitleField(void);

// フィールドオブジェクトのGameObjectindexを所得
SET_OBJECT* GetTitleFieldObject(int* objectCount);