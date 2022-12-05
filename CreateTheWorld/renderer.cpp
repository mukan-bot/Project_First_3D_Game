#include "renderer.h"


ID3D11Device* g_pDevice;		// DirectX11のデバイス
ID3D11DeviceContext* g_pDeviceContext;	// 描画用のデバイスコンテキスト
IDXGISwapChain* g_pSwapChain;		// 画面出力用のスワップチェイン
ID3D11RenderTargetView* g_pRenderTargetView;	// 画面出力用のレンダーターゲット


HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) {

	DXGI_SWAP_CHAIN_DESC desc{};
	// バッファ情報の設定
	desc.BufferCount = 1;
	desc.BufferDesc.Width = SCREEN_WIDTH;
	desc.BufferDesc.Height = SCREEN_HEIGHT;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// MSAAの設定
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	// ウィンドウ設定
	desc.Windowed = bWindow;
	desc.OutputWindow = hWnd;

	//	機能レベル
	const D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,		// DirectX 11.0
		//D3D_FEATURE_LEVEL_10_1,	// DirectX 10.1
		//D3D_FEATURE_LEVEL_10_0,	// DirectX 10.0
	};
	UINT NumFeatureLevels = ARRAYSIZE(FeatureLevels);

	D3D_FEATURE_LEVEL level;
	HRESULT hr;
	//	デバイスを作成
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

	// レンダーバッファの取得
	ID3D11Texture2D* pBuffer;
	if (FAILED(g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer)))
	{
		UninitRenderer();
		return false;
	}
	// レンダーターゲットビューの生成
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



// 画面のクリア
void ClearTarget(float r, float g, float b) {
	const float color[4]{ r, g, b, 1.0f };
	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, color);
}
// 画面のフリップ
void Present() {
	g_pSwapChain->Present(1, 0);
}












//デバイスの所得
ID3D11Device* GetDevice(void) { return g_pDevice; }
// デバイスコンテキストの取得
ID3D11DeviceContext* GetContext(void) { return g_pDeviceContext; }
// スワップチェインの取得
IDXGISwapChain* GetSwapChain(void) { return g_pSwapChain; }	
// レンダーターゲットの取得
ID3D11RenderTargetView* GetRenderTargetView() { return g_pRenderTargetView; }