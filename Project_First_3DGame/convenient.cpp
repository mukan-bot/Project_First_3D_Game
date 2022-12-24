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

void OutputXMFLOAT3Debug(char* name, XMFLOAT3 a) {
    OutputDebug("%s:%.2f,%.2f,%.2f\n", name, a.x, a.y, a.z);
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

    // �o�E���f�B���O�{�b�N�X(BB)�̏���
    if ((pos1.x + tempSize1.x > pos2.x - tempSize2.x) &&
        (pos1.x - tempSize1.x < pos2.x + tempSize2.x) &&
        (pos1.y + tempSize1.y > pos2.y - tempSize2.y) &&
        (pos1.y - tempSize1.y < pos2.y + tempSize2.y) &&
        (pos1.z + tempSize1.z > pos2.z - tempSize2.z) &&
        (pos1.z - tempSize1.z < pos2.z + tempSize2.z))
    {
        // �����������̏���
        ans = true;
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

