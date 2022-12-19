//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"

#include "input_M.h"
#include "collision.h"
#include "field.h"
#include "player.h"



HRESULT InitGame(void) {
	InitPlayer();

	InitField();

	SetCursorMove(false);

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