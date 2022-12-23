#pragma once
#include "main.h"
#include "model.h"


struct SET_MODEL {
	//char* model_path;
	char* name;
	DX11_MODEL model;
	int objIndex;
	//int mdlIndex;
	int colIndex;
};


HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);