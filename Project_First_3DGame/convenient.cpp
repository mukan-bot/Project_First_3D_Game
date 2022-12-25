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


bool RayCast(XMFLOAT3 xp0, XMFLOAT3 xp1, XMFLOAT3 xp2, XMFLOAT3 xpos, XMFLOAT3 xvec, XMFLOAT3* hit, XMFLOAT3* normal)
{
    XMVECTOR	p0 = XMLoadFloat3(&xp0);
    XMVECTOR	p1 = XMLoadFloat3(&xp1);
    XMVECTOR	p2 = XMLoadFloat3(&xp2);
    XMVECTOR	pos0 = XMLoadFloat3(&xpos);
    xvec = AddXMFLOAT3(xvec, xpos);
    XMVECTOR	pos1 = XMLoadFloat3(&xvec);

    XMVECTOR	nor;	// ポリゴンの法線
    XMVECTOR	vec1;
    XMVECTOR	vec2;
    float		d1, d2;

    {	// ポリゴンの外積をとって法線を求める(この処理は固定物なら予めInit()で行っておくと良い)
        vec1 = p1 - p0;
        vec2 = p2 - p0;
        CrossProduct(&nor, &vec2, &vec1);
        nor = XMVector3Normalize(nor);		// 計算しやすいように法線をノーマライズしておく(このベクトルの長さを１にしている)
        XMStoreFloat3(normal, nor);			// 求めた法線を入れておく
    }

    // ポリゴン平面と線分の内積とって衝突している可能性を調べる（鋭角なら＋、鈍角ならー、直角なら０）
    vec1 = pos0 - p0;
    vec2 = pos1 - p0;
    {	// 求めたポリゴンの法線と２つのベクトル（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
        d1 = DotProduct(&vec1, &nor);
        d2 = DotProduct(&vec2, &nor);
        if (((d1 * d2) > 0.0f) || (d1 == 0 && d2 == 0))
        {
            // 当たっている可能性は無い
            return(false);
        }
    }


    {	// ポリゴンと線分の交点を求める
        d1 = (float)fabs(d1);	// 絶対値を求めている
        d2 = (float)fabs(d2);	// 絶対値を求めている
        float a = d1 / (d1 + d2);							// 内分比

        XMVECTOR	vec3 = (1 - a) * vec1 + a * vec2;		// p0から交点へのベクトル
        XMVECTOR	p3 = p0 + vec3;							// 交点
        XMStoreFloat3(hit, p3);								// 求めた交点を入れておく

        {	// 求めた交点がポリゴンの中にあるか調べる

            // ポリゴンの各辺のベクトル
            XMVECTOR	v1 = p1 - p0;
            XMVECTOR	v2 = p2 - p1;
            XMVECTOR	v3 = p0 - p2;

            // 各頂点と交点とのベクトル
            XMVECTOR	v4 = p3 - p1;
            XMVECTOR	v5 = p3 - p2;
            XMVECTOR	v6 = p3 - p0;

            // 外積で各辺の法線を求めて、ポリゴンの法線との内積をとって符号をチェックする
            XMVECTOR	n1, n2, n3;

            CrossProduct(&n1, &v4, &v1);
            if (DotProduct(&n1, &nor) < 0.0f) return(false);	// 当たっていない

            CrossProduct(&n2, &v5, &v2);
            if (DotProduct(&n2, &nor) < 0.0f) return(false);	// 当たっていない

            CrossProduct(&n3, &v6, &v3);
            if (DotProduct(&n3, &nor) < 0.0f) return(false);	// 当たっていない
        }
    }

    return(true);	// 当たっている！(hitには当たっている交点が入っている。normalには法線が入っている)
}