#include "M_game.h"

#include "field.h"
#include "player.h"



HRESULT InitGame(void) {
	InitPlayer();

	InitField();

	return S_OK;
}
void UninitGame(void) {
	UninitPlayer();

}
void UpdateGame(void) {
	UpdatePlayer();

}
void DrawGame(void) {
	DrawPlayer();

}