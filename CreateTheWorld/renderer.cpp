#include "renderer.h"


ID3D11Device* g_pDevice;		// DirectX11�̃f�o�C�X
ID3D11DeviceContext* g_pDeviceContext;	// �`��p�̃f�o�C�X�R���e�L�X�g
IDXGISwapChain* g_pSwapChain;		// ��ʏo�͗p�̃X���b�v�`�F�C��
ID3D11RenderTargetView* g_pRenderTargetView;	// ��ʏo�͗p�̃����_�[�^�[�Q�b�g


HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) {

	DXGI_SWAP_CHAIN_DESC desc{};
	// �o�b�t�@���̐ݒ�
	desc.BufferCount = 1;
	desc.BufferDesc.Width = SCREEN_WIDTH;
	desc.BufferDesc.Height = SCREEN_HEIGHT;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// MSAA�̐ݒ�
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	// �E�B���h�E�ݒ�
	desc.Windowed = bWindow;
	desc.OutputWindow = hWnd;

	//	�@�\���x��
	const D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,		// DirectX 11.0
		//D3D_FEATURE_LEVEL_10_1,	// DirectX 10.1
		//D3D_FEATURE_LEVEL_10_0,	// DirectX 10.0
	};
	UINT NumFeatureLevels = ARRAYSIZE(FeatureLevels);

	D3D_FEATURE_LEVEL level;
	HRESULT hr;
	//	�f�o�C�X���쐬
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		FeatureLevels,
		NumFeatureLevels,
		D3D11_SDK_VERSION,
		&desc,
		&g_pSwapChain,
		&g_pDevice,
		&level,
		&g_pDeviceContext
	);
	if (FAILED(hr))
	{
		return hr;
	}

	// �����_�[�o�b�t�@�̎擾
	ID3D11Texture2D* pBuffer;
	if (FAILED(g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer)))
	{
		UninitRenderer();
		return false;
	}
	// �����_�[�^�[�Q�b�g�r���[�̐���
	if (FAILED(g_pDevice->CreateRenderTargetView(pBuffer, NULL, &g_pRenderTargetView)))
	{
		UninitRenderer();
		return false;
	}
	//SafeRelease(pBuffer);







	return S_OK;
}


void UninitRenderer(void) {
	g_pDevice->Release();
	g_pDeviceContext->Release();
	g_pSwapChain->Release();
}



// ��ʂ̃N���A
void ClearTarget(float r, float g, float b) {
	const float color[4]{ r, g, b, 1.0f };
	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, color);
}
// ��ʂ̃t���b�v
void Present() {
	g_pSwapChain->Present(1, 0);
}












//�f�o�C�X�̏���
ID3D11Device* GetDevice(void) { return g_pDevice; }
// �f�o�C�X�R���e�L�X�g�̎擾
ID3D11DeviceContext* GetContext(void) { return g_pDeviceContext; }
// �X���b�v�`�F�C���̎擾
IDXGISwapChain* GetSwapChain(void) { return g_pSwapChain; }	
// �����_�[�^�[�Q�b�g�̎擾
ID3D11RenderTargetView* GetRenderTargetView() { return g_pRenderTargetView; }