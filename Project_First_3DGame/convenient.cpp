//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

#include "convenient.h"



//OutputDebugStringをprintfみたいに使う。
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

void OutputXMFLOAT3Debug(char* name, XMFLOAT3 a) {
    OutputDebug("%s:%.2f,%.2f,%.2f\n", name, a.x, a.y, a.z);
}



//XYをXYZの回転に変換して加算
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}

//XMFLOAT3同士の足し算
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}
//XMFLOAT3同士の引き算
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}
//XMFLOAT3同士の掛け算
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
}
//XMFLOAT3同士の割り算
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z);
}

//引数の値でXMFLOAT３を初期化する
XMFLOAT3 SetXMFLOAT3(float set) {
    return XMFLOAT3(set, set, set);
}



//値の最大値と最小値を指定出来る
float Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}




// 内積(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2) {
    XMVECTOR temp = XMVector3Dot(*v1, *v2);
    float ans = 0.0f;
    XMStoreFloat(&ans, temp);
    return(ans);
}

// 外積(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2) {
    // ダイレクトＸでは、、、
    *ret = XMVector3Cross(*v1, *v2);
}

//XMFLOAT3のノーマライズ
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3) {
    XMFLOAT3 ans = vf3;

    XMVECTOR vec = XMLoadFloat3(&ans);

    XMStoreFloat3(&ans, XMVector3Normalize(vec));

    return ans;

}

//XMFLOAT3の比較
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    bool ans = false;
    if (a.x != b.x || a.y != b.y || a.z != b.z) {
        ans = true;
    }
    return ans;
}

//二点間の距離（β）
float LengthXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    float ans = 0.0f;

    XMVECTOR temp = XMLoadFloat3(&a) - XMLoadFloat3(&b);
    XMStoreFloat(&ans, temp);

    return ans;
}

//BBの当たり判定（回転は指定できない）
bool CollisionBB(XMFLOAT3 pos1, XMFLOAT3 size1, XMFLOAT3 pos2, XMFLOAT3 size2) {
    bool ans = false;

    XMFLOAT3 tempSize1 = DivXMFLOAT3(size1, SetXMFLOAT3(2.0f));
    XMFLOAT3 tempSize2 = DivXMFLOAT3(size2, SetXMFLOAT3(2.0f));

    // バウンディングボックス(BB)の処理
    if ((pos1.x + tempSize1.x > pos2.x - tempSize2.x) &&
        (pos1.x - tempSize1.x < pos2.x + tempSize2.x) &&
        (pos1.y + tempSize1.y > pos2.y - tempSize2.y) &&
        (pos1.y - tempSize1.y < pos2.y + tempSize2.y) &&
        (pos1.z + tempSize1.z > pos2.z - tempSize2.z) &&
        (pos1.z - tempSize1.z < pos2.z + tempSize2.z))
    {
        // 当たった時の処理
        ans = true;
    }



    return ans;

}

//BCの当たり判定
bool CollisionBC(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2) {
    BOOL ans = false;

    // 半径を2乗した物
    float len = (r1 + r2) * (r1 + r2);
    XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&pos2);

    // 2点間の距離（2乗した物）
    temp = XMVector3LengthSq(temp);
    float lenSq = 0.0f;
    XMStoreFloat(&lenSq, temp);

    if (len > lenSq) {
        ans = true;
    }

    return ans;
}




void GetLevel_Csv(FILE* fp, int index, LEVEL_ELEMENT* ans) {
  
    if (fp != NULL) {
        int i = 0;
        char name[256];
        XMFLOAT3 pos, rot, scl;
        while (fscanf_s(fp, "\n%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", name, _countof(name), &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &scl.x, &scl.y, &scl.z) != EOF)
        {
            if (i == index) {
                strcpy_s(ans->name, name);
                ans->pos = pos;
                ans->rot = rot;
                ans->scl = scl;
                return;
            }
            i++;
        }
    }
    ans = NULL;
    return ;
}

