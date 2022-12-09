#include "main.h"
#include "dae_model.h"

#include <stdio.h>
#include <string>




int xmlParse(char* sorce, char* tag, char* data) {
	char tagStart[64];
	char tagEnd[64];
	int dataLen = 0;
	sprintf_s(tagStart, "<%s>", tag);
	sprintf_s(tagEnd, "</%s>", tag);


	/////�ϐ�����������
	//�f�[�^�̒������v�Z
	dataLen = strlen(tagStart) - strlen(strstr(sorce, tagEnd));
	dataLen = strlen(strstr(sorce, tagStart));

	memset(data, '\0', strlen(sorce) + 1); //�\�[�X�Ɠ���������/0�����Ă���
	memcpy(data, strstr(sorce, tagStart) + strlen(tagStart), dataLen);


#ifdef _DEBUG
	OutputDebug(data);
#endif // _DEBUG

	return 0;
}





void LoadDaeModel(DAE_MOEL* model, char* filePath) {

	FILE* fp;
	fopen_s(&fp, filePath, "r");

	//�t�@�C���T�C�Y�̎擾
	fpos_t fsize;
	fseek(fp, 0, SEEK_END);   //�t�@�C���|�C���^���t�@�C���̍Ō�Ɉړ�������B
	fsize = ftell(fp) + 1;        //�t�@�C���T�C�Y���擾����B(�ǂ���ł�OK)    //fgetpos(fp,&fsize);        //�t�@�C���T�C�Y���擾����B(�ǂ���ł�OK)
	fseek(fp, 0L, SEEK_SET);  //�t�@�C���|�C���^��擪�ɖ߂��B

	//�t�@�C���T�C�Y���̗̈���m��
	char* strBuffer = (char*)malloc((size_t)(fsize) * sizeof(char));//�I�[�R�[�h����]���Ɋm��

	//�t�@�C���̓ǂݍ���
	fsize = fread(strBuffer, sizeof(char), (size_t)fsize, fp);
	fclose(fp);

	strBuffer[fsize] = '\0';

	//����
#ifdef _DEBUG
	OutputDebug("���f���T�C�Y�F%d\n", fsize);
#endif // _DEBUG


	free(strBuffer);        //�������̉��


}




