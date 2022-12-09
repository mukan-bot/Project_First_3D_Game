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


	/////変数初期化完了
	//データの長さを計算
	dataLen = strlen(tagStart) - strlen(strstr(sorce, tagEnd));
	dataLen = strlen(strstr(sorce, tagStart));

	memset(data, '\0', strlen(sorce) + 1); //ソースと同じ長さに/0を入れておく
	memcpy(data, strstr(sorce, tagStart) + strlen(tagStart), dataLen);


#ifdef _DEBUG
	OutputDebug(data);
#endif // _DEBUG

	return 0;
}





void LoadDaeModel(DAE_MOEL* model, char* filePath) {

	FILE* fp;
	fopen_s(&fp, filePath, "r");

	//ファイルサイズの取得
	fpos_t fsize;
	fseek(fp, 0, SEEK_END);   //ファイルポインタをファイルの最後に移動させる。
	fsize = ftell(fp) + 1;        //ファイルサイズを取得する。(どちらでもOK)    //fgetpos(fp,&fsize);        //ファイルサイズを取得する。(どちらでもOK)
	fseek(fp, 0L, SEEK_SET);  //ファイルポインタを先頭に戻す。

	//ファイルサイズ分の領域を確保
	char* strBuffer = (char*)malloc((size_t)(fsize) * sizeof(char));//終端コード分を余分に確保

	//ファイルの読み込み
	fsize = fread(strBuffer, sizeof(char), (size_t)fsize, fp);
	fclose(fp);

	strBuffer[fsize] = '\0';

	//処理
#ifdef _DEBUG
	OutputDebug("モデルサイズ：%d\n", fsize);
#endif // _DEBUG


	free(strBuffer);        //メモリの解放


}




