#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"




HRESULT InitTitle(void) {

	InitTitleBG();
	InitTitleUI();
	return S_OK;
}
void UninitTitle(void) {
	UninitTitleBG();
	UninitTitleUI();
}
void UpdateTitle(void) {
	UpdateTitleBG();
	UpdateTitleUI();
}
void DrawTitle(void) {
	DrawTitleBG();
	DrawTitleUI();
}