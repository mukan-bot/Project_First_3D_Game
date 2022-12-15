//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "dllmain.h"

#include <string>

//DLL読み込み時の実行（初期処理）
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){
#ifdef _DEBUG
    OutputDebugString("DLL読み込み成功(多分)\n");
#endif // _DEBUG

    return true;
}


//OutputDebugStringをprintfみたいに使う。
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




//XYをXYZの回転に変換して加算
DLLEXPOERT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}

//XMFLOAT3同士の足し算
DLLEXPOERT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z); 
}
//XMFLOAT3同士の引き算
DLLEXPOERT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z); 
}
//XMFLOAT3同士の掛け算
DLLEXPOERT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z); 
}
//XMFLOAT3同士の割り算
DLLEXPOERT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z); 
}



//値の最大値と最小値を指定出来る
DLLEXPOERT float Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}




// 内積(dot)
DLLEXPOERT float DotProduct(XMVECTOR* v1, XMVECTOR* v2){
    XMVECTOR temp = XMVector3Dot(*v1, *v2);
    float ans = 0.0f;
    XMStoreFloat(&ans, temp);
    return(ans);
}

// 外積(cross)
DLLEXPOERT void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2){
    // ダイレクトＸでは、、、
    * ret = XMVector3Cross(*v1, *v2);
}

//XMFLOAT3のノーマライズ
DLLEXPOERT XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3) {
    XMFLOAT3 ans = vf3;

    XMVECTOR vec = XMLoadFloat3(&ans);

    XMStoreFloat3(&ans, XMVector3Normalize(vec));

    return ans;

}

//XMFLOAT3の比較
DLLEXPOERT bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    bool ans = false;
    if (a.x != b.x || a.y != b.y || a.z != b.z) {
        ans = true;
    }
    return ans;
}





