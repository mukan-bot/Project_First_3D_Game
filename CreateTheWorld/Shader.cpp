#include "dxmain.h"
#include "Shader.h"

// シェーダコンパイル周りの機能をインクルード
#include <d3dcompiler.h>
// シェーダコンパイル用の静的ライブラリをリンク
#pragma comment(lib,"d3dcompiler.lib")


static ID3D11PixelShader* g_PixelShader = NULL;


static ID3D11VertexShader* g_VertexShader = NULL;
ID3DBlob* g_pVSCode;

HRESULT InitShader(void){


	ID3D11Device* pDevice = GetDevice();


	//PSシェダーコンパイル
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
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)pPSErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);
		//SafeRelease(pErrorMsg);
	}
	else
	{
		HRESULT hr;
		// ピクセルシェーダの生成
		hr = pDevice->CreatePixelShader(
			pPSCode->GetBufferPointer(),
			pPSCode->GetBufferSize(),
			NULL,
			&g_PixelShader
		);

	}



	//VSシェダーコンパイル
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
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)pVSErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);
		//SafeRelease(pErrorMsg);
	}
	else
	{
		// コンパイル成功
		HRESULT hr;
		// 頂点シェーダの生成
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

