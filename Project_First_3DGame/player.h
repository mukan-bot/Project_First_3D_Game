//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

// �v���C���[��GameObject�̃C���f�b�N�X������
int GetPlayerGameObjectIndex(void);
// �v���C���[�̃R���W������GameObject�̃C���f�b�N�X������
int GetPlayerColObjectIndex(void);
// �v���C���[�̍U���n�̓����蔻���GameObject�̃C���f�b�N�X������
int GetPlayerHitColObjectIndex(void);
// �v���C���[��HP������
int GetPlayerHP(void);