//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

//よく使う計算とかを関数として持っておく

#pragma once

#include "main.h"


//幅と高さ(XMFLOAT○と同じように使える)
struct WHSIZE {
	float w;	//幅
	float h;	//高さ

	//WHSIZE(0.0f,0.0f);みたいな感じで代入出来るように
	WHSIZE() = default;

	WHSIZE(const WHSIZE&) = default;
	WHSIZE& operator=(const WHSIZE&) = default;

	WHSIZE(WHSIZE&&) = default;
	WHSIZE& operator=(WHSIZE&&) = default;

	constexpr WHSIZE(float _w, float _h) : w(_w), h(_h) {}
	explicit WHSIZE(_In_reads_(2) const float* pArrah) : w(pArrah[0]), h(pArrah[1]) {}
};




void OutputDebug(const char* format, ...);

//XYをXYZの回転に変換して加算
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3同士の足し算
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の引き算
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の掛け算
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の割り算
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//引数の値でXMFLOAT３を初期化する
XMFLOAT3 SetXMFLOAT3(float set);

//値の最大値と最小値を指定出来る
float Clamp(float value, float min, float max);

// 内積(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// 外積(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 正規化
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3の比較
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//二点間の距離（β）
float LengthXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);


//BBの当たり判定（回転は指定できない）
//当たっていたらTrueを返す
bool CollisionBB(XMFLOAT3 pos1, XMFLOAT3 size1, XMFLOAT3 pos2, XMFLOAT3 size2);
//BCの当たり判定
//当たっていたらTrueを返す
bool CollisionBC(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2);



//SCVファイルから情報を所得する
char* get_element(const char* file_name, int row, int col);
//CSVファイルのエレメントの位置を所得する
int get_row_col(const char* file_name, const char* element, int* row, int* col);