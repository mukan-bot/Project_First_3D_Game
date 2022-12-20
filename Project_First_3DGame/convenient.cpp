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

//�����̒l��XMFLOAT�R������������
XMFLOAT3 SetXMFLOAT3(float set) {
    return XMFLOAT3(set, set, set);
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

//��_�Ԃ̋����i���j
float LengthXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    float ans = 0.0f;

    XMVECTOR temp = XMLoadFloat3(&a) - XMLoadFloat3(&b);
    XMStoreFloat(&ans, temp);

    return ans;
}

//BB�̓����蔻��i��]�͎w��ł��Ȃ��j
bool CollisionBB(XMFLOAT3 pos1, XMFLOAT3 size1, XMFLOAT3 pos2, XMFLOAT3 size2) {
    bool ans = false;

    XMFLOAT3 tempSize1 = DivXMFLOAT3(size1, SetXMFLOAT3(2.0f));
    XMFLOAT3 tempSize2 = DivXMFLOAT3(size2, SetXMFLOAT3(2.0f));

    //MEMO:pos1�������O�ɂ���
    pos1 = SubXMFLOAT3(pos1, tempSize1);
    //MEMO:pos2���E����O�ɂ���
    pos2 = AddXMFLOAT3(pos2, tempSize2);

    //pos2 = AddXMFLOAT3(pos2, size2);

    //�����O�ƉE����������
    if ((pos1.x > pos2.x) &&
        (pos1.y > pos2.y)) {

        pos1 = AddXMFLOAT3(pos1, size1);
        pos2 = SubXMFLOAT3(pos2, size2);

        if ((pos1.x > pos2.x) &&
            (pos1.y > pos2.y)) {
            ans = true;
        }
    }

    return ans;

}

//BC�̓����蔻��
bool CollisionBC(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2) {
    BOOL ans = false;

    // ���a��2�悵����
    float len = (r1 + r2) * (r1 + r2);
    XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&pos2);

    // 2�_�Ԃ̋����i2�悵�����j
    temp = XMVector3LengthSq(temp);
    float lenSq = 0.0f;
    XMStoreFloat(&lenSq, temp);

    if (len > lenSq) {
        ans = true;
    }

    return ans;
}






char* get_element(const char* file_name, int row, int col){
    char buffer[BUFFER_SIZE];
    char* element = NULL;

    FILE* fp;
    fopen_s(&fp,file_name, "r");
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }

    // �s��ǂݍ���ŁA�w�肳�ꂽ�s�ɓ��B����܂ŌJ��Ԃ�
    for (int i = 0; i <= row; i++) {
        if (fgets(buffer, BUFFER_SIZE, fp) == NULL) {
            // �t�@�C���̍Ō�ɓ��B�������A�G���[�����������ꍇ
            break;
        }
        if (i == row) {
            // �w�肳�ꂽ�s���������ꍇ�A�J���}�ŋ�؂�������擾����
            char* context1;
            char* p = strtok_s(buffer, ",", &context1);
            for (int j = 0; j < col; j++) {

                char* context2;
                p = strtok_s(NULL, ",", &context2);
            }
            element = p;
        }
    }

    fclose(fp);

    return element;
}


int get_row_col(const char* file_name, const char* element, int* row, int* col){
    char buffer[BUFFER_SIZE];

    // CSV�t�@�C�����J��
    FILE* fp;
    fopen_s(&fp, file_name, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    // �s��ǂݍ���ŁA�v�f��������܂ŌJ��Ԃ�
    int i = 0;
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char* context1;
        // �J���}�ŋ�؂�������擾����
        char* p = strtok_s(buffer, ",", &context1);
        int j = 0;
        while (p != NULL) {
            if (strcmp(p, element) == 0) {
                // �v�f�����������̂ŁA�s�ԍ��Ɨ�ԍ���Ԃ�
                *row = i;
                *col = j;
                fclose(fp);
                return 0;
            }
            char* context2;
            p = strtok_s(NULL, ",", &context2);
            j++;
        }
        i++;
    }

    // �v�f��������Ȃ�����
    fclose(fp);
    return 1;
}
