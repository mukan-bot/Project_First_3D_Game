#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct GAME_OBJECT
{
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	bool use;
};

int SetGameObject(void);
void DelGameObject(int index);

void SetPosition(int index, XMFLOAT3 position);
void SetRotation(int index, XMFLOAT3 rotation);
void SetScale(int index, XMFLOAT3 scale);

XMFLOAT3 GetPosition(int index);
XMFLOAT3 GetRotation(int index);
XMFLOAT3 GetScale(int index);