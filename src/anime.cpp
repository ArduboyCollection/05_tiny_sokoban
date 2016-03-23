#include "anime.h"
#include "lv.h"
#include "res.h"

//---------------------------------------------------------------------------
ST_ANIME Anime;


//---------------------------------------------------------------------------
void AnimeInit(void)
{
	_Memset(&Anime, 0x00, sizeof(ST_ANIME));

	Anime.isEnd = TRUE;
}
//---------------------------------------------------------------------------
void AnimeExec(void)
{
	switch(Anime.step)
	{
	case 0:
		AnimeExecSub();
		Anime.step++;
		break;

	case 1:
		if(++Anime.stepCnt >= 8)
		{
			Anime.step++;
		}
		break;

	case 2:
		Anime.x  += Anime.tx;
		Anime.y  += Anime.ty;
		Anime.bx += Anime.tx;
		Anime.by += Anime.ty;
		AnimeExecSub();

		Anime.isEnd = TRUE;
		break;
	}
}
//---------------------------------------------------------------------------
void AnimeExecSub(void)
{
	LvSetCodeTurnChr(Anime.x, Anime.y);

	if(Anime.isBox == TRUE)
	{
		LvSetCodeTurnBox(Anime.bx, Anime.by);
	}
}
//---------------------------------------------------------------------------
void AnimeDraw(void)
{
	s8 cx = Anime.x  * 8 + Anime.tx * Anime.stepCnt;
	s8 cy = Anime.y  * 8 + Anime.ty * Anime.stepCnt;
	s8 bx = Anime.bx * 8 + Anime.tx * Anime.stepCnt;
	s8 by = Anime.by * 8 + Anime.ty * Anime.stepCnt;

	ResDrawChr2(cx, cy);

	if(Anime.isBox == TRUE)
	{
		ResDrawBox2(bx, by);
	}
}
//---------------------------------------------------------------------------
void AnimeSetChr(u8 x, u8 y)
{
	Anime.x = x;
	Anime.y = y;
}
//---------------------------------------------------------------------------
u16 AnimeGetMoveCnt(void)
{
	return Anime.move;
}
//---------------------------------------------------------------------------
void AnimeCalcMove(s8 tx, s8 ty)
{
	s8 dx1 = Anime.x + tx;
	s8 dy1 = Anime.y + ty;
	s8 dx2 = Anime.x + tx + tx;
	s8 dy2 = Anime.y + ty + ty;

	// �ړ��`�F�b�N
	if(LvIsWall(dx1, dy1) == TRUE)
	{
		return;
	}

	if(LvIsBox(dx1, dy1) == TRUE)
	{
		if(LvIsBox(dx2, dy2) == TRUE || LvIsWall(dx2, dy2) == TRUE)
		{
			return;
		}
	}


	// �ړ�����
	Anime.tx    = tx;
	Anime.ty    = ty;
	Anime.bx    = dx1;
	Anime.by    = dy1;
	Anime.isBox = LvIsBox(dx1, dy1);

	Anime.step = 0;
	Anime.stepCnt = 0;
	Anime.isEnd = FALSE;


	AnimeAddHistory(tx, ty, Anime.isBox);
}
//---------------------------------------------------------------------------
void AnimeCalcMoveU(void)
{
	AnimeCalcMove( 0, -1);
}
//---------------------------------------------------------------------------
void AnimeCalcMoveD(void)
{
	AnimeCalcMove( 0,  1);
}
//---------------------------------------------------------------------------
void AnimeCalcMoveL(void)
{
	AnimeCalcMove(-1,  0);
}
//---------------------------------------------------------------------------
void AnimeCalcMoveR(void)
{
	AnimeCalcMove( 1,  0);
}
//---------------------------------------------------------------------------
void AnimeCalcPrev(void)
{
	if(Anime.cnt == 0)
	{
		return;
	}
	Anime.cnt--;

	if(Anime.cur == 0)
	{
		Anime.cur = ANIME_MAX_MOVE_CNT;
	}
	Anime.cur--;

	Anime.move--;


	s8 tx   = Anime.m.tx[Anime.cur];
	s8 ty   = Anime.m.ty[Anime.cur];
	bool is = Anime.m.isBox[Anime.cur];

	Anime.tx    = tx * -1;
	Anime.ty    = ty * -1;
	Anime.bx    = Anime.x + tx;
	Anime.by    = Anime.y + ty;
	Anime.isBox = is;

	Anime.step = 0;
	Anime.stepCnt = 0;
	Anime.isEnd = FALSE;
}
//---------------------------------------------------------------------------
void AnimeAddHistory(s8 tx, s8 ty, bool isBox)
{
	Anime.m.tx[Anime.cur] = tx;
	Anime.m.ty[Anime.cur] = ty;
	Anime.m.isBox[Anime.cur] = isBox;

	Anime.move++;

	Anime.cur++;
	Anime.cur %= ANIME_MAX_MOVE_CNT;

	if(Anime.cnt < ANIME_MAX_MOVE_CNT-1)
	{
		Anime.cnt++;
	}
}
//---------------------------------------------------------------------------
bool AnimeIsEnd(void)
{
	return Anime.isEnd;
}
