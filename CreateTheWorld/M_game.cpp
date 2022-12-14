#include "M_game.h"

#include "player.h"



HRESULT InitGame(void) {
	InitPlayer();

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