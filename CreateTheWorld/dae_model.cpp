#include "main.h"
#include "dae_model.h"

#include <stdio.h>
#include <string>



void LoadDaeModel(DAE_MOEL* model, char* filePath) {

	FILE* fp;
	fopen_s(&fp, filePath, "r");

	//�t�@�C���T�C�Y�̎擾
	fpos_t fsize;
	fseek(fp, 0, SEEK_END);   //�t�@�C���|�C���^���t�@�C���̍Ō�Ɉړ�������B
	fsize = ftell(fp);        //�t�@�C���T�C�Y���擾����B(�ǂ���ł�OK)    //fgetpos(fp,&fsize);        //�t�@�C���T�C�Y���擾����B(�ǂ���ł�OK)
	fseek(fp, 0L, SEEK_SET);  //�t�@�C���|�C���^��擪�ɖ߂��B

	//�t�@�C���T�C�Y���̗̈���m��
	char* strBuffer = (char*)malloc((size_t)(fsize) * sizeof(char));//�I�[�R�[�h����]���Ɋm��

	//�t�@�C���̓ǂݍ���
	fsize = fread(strBuffer, sizeof(char), (size_t)fsize, fp);
	fclose(fp);

	strBuffer[fsize] = '\0';

	//����
	OutputDebug("%d", fsize);

	free(strBuffer);        //�������̉��


}