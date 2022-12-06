#pragma once

#include"main.h"



HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

// 画面のクリア
void ClearTarget(float r, float g, float b);
// 画面のフリップ
void Present();


ID3D11Device* GetDevice(void);			//デバイスの所得
ID3D11DeviceContext* GetContext(void);	// デバイスコンテキストの取得
IDXGISwapChain* GetSwapChain(void);		// スワップチェインの取得
ID3D11RenderTargetView* GetRenderTargetView();	//// 画面出力用のレンダーターゲット