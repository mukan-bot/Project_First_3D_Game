#include "main.h"
#include "dae_model.h"

#include <stdio.h>
#include <string>



void LoadDaeModel(DAE_MOEL* model, char* filePath) {

	FILE* fp;
	fopen_s(&fp, filePath, "r");

	//ファイルサイズの取得
	fpos_t fsize;
	fseek(fp, 0, SEEK_END);   //ファイルポインタをファイルの最後に移動させる。
	fsize = ftell(fp);        //ファイルサイズを取得する。(どちらでもOK)    //fgetpos(fp,&fsize);        //ファイルサイズを取得する。(どちらでもOK)
	fseek(fp, 0L, SEEK_SET);  //ファイルポインタを先頭に戻す。

	//ファイルサイズ分の領域を確保
	char* strBuffer = (char*)malloc((size_t)(fsize) * sizeof(char));//終端コード分を余分に確保

	//ファイルの読み込み
	fsize = fread(strBuffer, sizeof(char), (size_t)fsize, fp);
	fclose(fp);

	strBuffer[fsize] = '\0';

	//処理
	OutputDebug("%d", fsize);

	free(strBuffer);        //メモリの解放


}