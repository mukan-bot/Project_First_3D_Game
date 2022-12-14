//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "dllmain.h"

#include <string>

//DLL�ǂݍ��ݎ��̎��s�i���������j
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){
#ifdef _DEBUG
    OutputDebugString("DLL�ǂݍ��ݐ���(����)\n");
#endif // _DEBUG

    return true;
}


//OutputDebugString��printf�݂����Ɏg���B
DLLEXPOERT void OutputDebug(const char* format, ...) {
#ifdef _DEBUG

    char szBufDebug[4096] = "";

    va_list arg;

    va_start(arg, format);
    vsprintf_s(szBufDebug, format, arg);
    va_end(arg);

    OutputDebugString(szBufDebug);

#endif // DEBUG
}




//XY��XYZ�̉�]�ɕϊ����ĉ��Z
DLLEXPOERT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}

//XMFLOAT3���m�̑����Z
DLLEXPOERT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z); 
}
//XMFLOAT3���m�̈����Z
DLLEXPOERT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z); 
}
//XMFLOAT3���m�̊|���Z
DLLEXPOERT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z); 
}
//XMFLOAT3���m�̊���Z
DLLEXPOERT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z); 
}



//�l�̍ő�l�ƍŏ��l���w��o����
DLLEXPOERT float Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}




// ����(dot)
DLLEXPOERT float DotProduct(XMVECTOR* v1, XMVECTOR* v2){
    XMVECTOR temp = XMVector3Dot(*v1, *v2);
    float ans = 0.0f;
    XMStoreFloat(&ans, temp);
    return(ans);
}

// �O��(cross)
DLLEXPOERT void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2){
    // �_�C���N�g�w�ł́A�A�A
    * ret = XMVector3Cross(*v1, *v2);
}










