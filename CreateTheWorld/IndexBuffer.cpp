#include "IndexBuffer.h"

ID3D11Buffer* g_pIndexBuffer;


HRESULT IndexBuffer(UINT size, void* pInitData) {
	ID3D11Device* pDevice = GetDevice();

	D3D11_BUFFER_DESC desc;
	// 頂点バッファの初期化設定
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	// 初期化時に設定するバッファデータ
	data.pSysMem = pInitData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateBuffer(&desc, &data, &g_pIndexBuffer)))
	{
		return false;
	}
	return S_OK;
}
ID3D11Buffer* GetIndexBuffer(void) {
	return g_pIndexBuffer;
}