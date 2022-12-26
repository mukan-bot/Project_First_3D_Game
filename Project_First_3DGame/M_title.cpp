#include "M_title.h"
#include "title_bg.h"




HRESULT InitTitle(void) {

	InitTitleBG();

	return S_OK;
}
void UninitTitle(void) {
	UninitTitleBG();
}
void UpdateTitle(void) {
	UpdateTitleBG();
}
void DrawTitle(void) {
	DrawTitleBG();
}