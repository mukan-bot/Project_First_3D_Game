#include "IndexBuffer.h"

ID3D11Buffer* g_pIndexBuffer;


HRESULT IndexBuffer(UINT size, void* pInitData) {
	ID3D11Device* pDevice = GetDevice();

	D3D11_BUFFER_DESC desc;
	// ���_�o�b�t�@�̏������ݒ�
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	// ���������ɐݒ肷��o�b�t�@�f�[�^
	data.pSysMem = pInitData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateBuffer(&desc, &data, &g_pIndexBuffer)))
	{
		return false;
	}
	return S_OK;
}
ID3D11Buffer* GetIndexBuffer(void) {
	return g_pIndexBuffer;
}