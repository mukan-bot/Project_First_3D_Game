//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include <string>

#include "convenient.h"


//OutputDebugString��printf�݂����Ɏg���B
void OutputDebug(const char* format, ...) {
#ifdef _DEBUG

    char szbufDebug[4096] = "";

    va_list arg;

    va_start(arg, format);
    vsprintf_s(szbufDebug, format, arg);
    va_end(arg);

    OutputDebugString(szbufDebug);

#endif // DEBUG
}




//XY��XYZ�̉�]�ɕϊ����ĉ��Z
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}

//XMFLOAT3���m�̑����Z
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}
//XMFLOAT3���m�̈����Z
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}
//XMFLOAT3���m�̊|���Z
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
}
//XMFLOAT3���m�̊���Z
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z);
}



//�l�̍ő�l�ƍŏ��l���w��o����
float Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}




// ����(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2) {
    XMVECTOR temp = XMVector3Dot(*v1, *v2);
    float ans = 0.0f;
    XMStoreFloat(&ans, temp);
    return(ans);
}

// �O��(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2) {
    // �_�C���N�g�w�ł́A�A�A
    *ret = XMVector3Cross(*v1, *v2);
}

//XMFLOAT3�̃m�[�}���C�Y
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3) {
    XMFLOAT3 ans = vf3;

    XMVECTOR vec = XMLoadFloat3(&ans);

    XMStoreFloat3(&ans, XMVector3Normalize(vec));

    return ans;

}

//XMFLOAT3�̔�r
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    bool ans = false;
    if (a.x != b.x || a.y != b.y || a.z != b.z) {
        ans = true;
    }
    return ans;
}





