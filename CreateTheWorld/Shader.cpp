#include "dxmain.h"
#include "Shader.h"

// �V�F�[�_�R���p�C������̋@�\���C���N���[�h
#include <d3dcompiler.h>
// �V�F�[�_�R���p�C���p�̐ÓI���C�u�����������N
#pragma comment(lib,"d3dcompiler.lib")


static ID3D11PixelShader* g_PixelShader = NULL;


static ID3D11VertexShader* g_VertexShader = NULL;
ID3DBlob* g_pVSCode;

HRESULT InitShader(void){


	ID3D11Device* pDevice = GetDevice();


	//PS�V�F�_�[�R���p�C��
	ID3DBlob* pPSCode;
	ID3DBlob* pPSErrorMsg;
	HRESULT ps_hr = D3DX11CompileFromFile(
		"ps.hlsl",
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		NULL,
		&pPSCode,
		&pPSErrorMsg,
		NULL
	);
	if (FAILED(ps_hr))
	{
		// �V�F�[�_�̃G���[���e��\��
		MessageBox(NULL, (char*)pPSErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);
		//SafeRelease(pErrorMsg);
	}
	else
	{
		HRESULT hr;
		// �s�N�Z���V�F�[�_�̐���
		hr = pDevice->CreatePixelShader(
			pPSCode->GetBufferPointer(),
			pPSCode->GetBufferSize(),
			NULL,
			&g_PixelShader
		);

	}



	//VS�V�F�_�[�R���p�C��
	ID3DBlob* pVSCode;
	ID3DBlob* pVSErrorMsg;
	HRESULT vs_hr = D3DX11CompileFromFile(
		".hlsl",
		NULL,
		NULL,
		"VS",
		"_5_0",
		0,
		0,
		NULL,
		&pPSCode,
		&pVSErrorMsg,
		NULL
	);
	if (FAILED(vs_hr))
	{
		// �V�F�[�_�̃G���[���e��\��
		MessageBox(NULL, (char*)pVSErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);
		//SafeRelease(pErrorMsg);
	}
	else
	{
		// �R���p�C������
		HRESULT hr;
		// ���_�V�F�[�_�̐���
		hr = pDevice->CreateVertexShader(
			pVSCode->GetBufferPointer(),
			pVSCode->GetBufferSize(),
			NULL,
			&g_VertexShader
		);
		if (FAILED(hr)) {
			//SafeRelease(pBlob);
			return false;
		}
		g_pVSCode = pVSCode;
	}


	return S_OK;
}

