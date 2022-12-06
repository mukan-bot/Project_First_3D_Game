#pragma once

#include "dxmain.h"

HRESULT IndexBuffer(UINT size, void* pInitData);
ID3D11Buffer* GetIndexBuffer(void);