#pragma once
#include "main.h"
#include "model.h"


struct SET_OBJECT {
	int gameObjectIndex;
	int gameModelIndex;
	int collisonIndex;
};


HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

SET_OBJECT* GetFieldObject(int* objectCount);