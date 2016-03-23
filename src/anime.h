#ifndef ANIME_H
#define ANIME_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_MOVE_CNT			50


//---------------------------------------------------------------------------

typedef struct {
	s8   tx[ANIME_MAX_MOVE_CNT];
	s8   ty[ANIME_MAX_MOVE_CNT];
	bool isBox[ANIME_MAX_MOVE_CNT];

} ST_ANIME_MOVE;


typedef struct {
	u8   step;
	u8   stepCnt;
	s8   x;						// �L�����N�^�̍��W
	s8   y;
	s8   bx;					// �{�b�N�X�̍��W
	s8   by;
	s8   tx;					// ����
	s8   ty;
	bool isBox;
	bool isEnd;

	u16  move;					// �ړ��J�E���^
	s8   cnt;					// �ړ��o�b�t�@�J�E���^
	s8   cur;					// �ړ��o�b�t�@�J�[�\��
	ST_ANIME_MOVE m;

} ST_ANIME;


//---------------------------------------------------------------------------
void AnimeInit(void);
void AnimeExec(void);
void AnimeExecSub(void);
void AnimeDraw(void);

void AnimeSetChr(u8 bx, u8 by);
u16  AnimeGetMoveCnt(void);

void AnimeCalcMove(s8 tx, s8 ty);
void AnimeCalcMoveU(void);
void AnimeCalcMoveD(void);
void AnimeCalcMoveL(void);
void AnimeCalcMoveR(void);

void AnimeCalcPrev(void);
void AnimeAddHistory(s8 tx, s8 ty, bool isBox);

bool AnimeIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
