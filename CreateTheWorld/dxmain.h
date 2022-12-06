#pragma once

#include"main.h"



HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

// ��ʂ̃N���A
void ClearTarget(float r, float g, float b);
// ��ʂ̃t���b�v
void Present();


ID3D11Device* GetDevice(void);			//�f�o�C�X�̏���
ID3D11DeviceContext* GetContext(void);	// �f�o�C�X�R���e�L�X�g�̎擾
IDXGISwapChain* GetSwapChain(void);		// �X���b�v�`�F�C���̎擾
ID3D11RenderTargetView* GetRenderTargetView();	//// ��ʏo�͗p�̃����_�[�^�[�Q�b�g