************************************************************************
*    							       *
*		[[[ NOP ]]]  COMMON SUBROUTINES			       *
*		by S.OKADA from 91/09/04 Wed 16:22		       *
*								       *
************************************************************************



		XDEF	SYS_FIRST_INIT,SYS_SECOND_INIT
		XDEF	LWORK_INIT,PWORK_INIT,LPWORK_INIT
		XDEF	FREE_PWORK,FREE_LWORK,AFTER_FREE_WORK
		XDEF	PWORK_SET
		XDEF	BIT_FLAG_CLEAR,BYTE_FLAG_CLEAR
		XDEF	RAND16,RAND8
		XDEF	SIN,COS,SIN_L,COS_L,MUL32,SEC_TIME,SEC_TIME_BCD
		XDEF	PLAYABLE
		XDEF	M_FIX_CLEAR
		XDEF	OBJ_MAP_SET

		XREF	?A5
;by SUB
		XREF	INIT_SOUND

		SECT.S	SYS,,C

		INCLUDE	NEO_GEO.INC	@@@
		INCLUDE	LABEL.INC
		INCLUDE	MACRO.INC	@@@
		INCLUDE	CML.INC		@@@

;
;	    *** system work initialize ***
;

SYS_FIRST_INIT:

;		initialize for interrupt enable

		MOVE.B	D0,PALETTE_BANK0
		MOVEQ.L	#0,D0
		MOVE.L	D0,(A5)
		MOVE.L	D0,4(A5)
		MOVE.B	D0,ERROR_LEVER(A5)
		MOVE.B	D0,TEMP_ORDER(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*0(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*1(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*2(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*3(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*4(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*5(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*6(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*7(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*8(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*9(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*10(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*11(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*12(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*13(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*14(A5)
		MOVE.W	D0,COLOR_BUFFER_0+32*16*15(A5)

		MOVE.L	D0,OBJ2_MAP(A5)
		MOVE.L	D0,OBJ2_MAP+4(A5)
		MOVE.L	D0,OBJ3_MAP(A5)
		MOVE.L	D0,OBJ3_MAP+4(A5)
		MOVE.L	D0,OBJ4_MAP(A5)
		MOVE.L	D0,OBJ4_MAP+4(A5)

		MOVE.W	#1,OBJ1_MAP(A5)
		MOVE.W	#380,OBJ1_MAP+2(A5)
		MOVE.W	#380,OBJ1_MAP+4(A5)
		MOVE.W	#-1,OBJ1_MAP+6(A5)

		MOVE.B	#80H,ORDER_BUFFER(A5)
		MOVE.B	#80H,ORDER_BUFFER+128(A5)
		MOVE.B	#100B,START_FLAG2(A5)
		MOVE.B	D0,MESS_BUSY(A5)
		MOVE.L	#MESS_BUFFER,MESS_POINT(A5)
		JSR	INIT_SOUND(PC)
		BSR	INFO_INIT
		BSR	SECOND_VALUE_SET

		RTS

INFO_INIT:

;		tool data infomation intialize

;*** tool data infomation ***

ALL_INFO_ADRS	EQU	0F8H

T_BACK_INFO	EQU	20H
T_PAL_IND_INFO	EQU	24H
T_OBJT_INFO	EQU	30H
T_PALETTE_INFO	EQU	40H


		MOVE.L	ALL_INFO_ADRS,A6
		MOVEQ.L	#0FH,D0
		MOVE.L	T_BACK_INFO(A6),BACK_INFO(A5)
		AND.W	D0,BACK_INFO(A5)
		MOVE.L	T_PAL_IND_INFO(A6),PAL_IND_INFO(A5)
		AND.W	D0,PAL_IND_INFO(A5)
		MOVE.L	T_OBJT_INFO(A6),OBJT_INFO(A5)
		AND.W	D0,OBJT_INFO(A5)
		MOVE.L	T_PALETTE_INFO(A6),PALETTE_INFO(A5)
		AND.W	D0,PALETTE_INFO(A5)
		RTS


SECOND_VALUE_SET:
		MOVE.B	#60,SECOND_VALUE(A5)
		MOVE.W	V_POSITION,D0
		BTST.L	#3,D0
		BEQ.S	SVS_1			NTSC mode

		MOVE.B	#50,SECOND_VALUE(A5)	PAL mode
SVS_1:
		RTS



SYS_SECOND_INIT:

;		intialize for all program

		JSR	LPWORK_INIT(PC)
		JSR	BIT_FLAG_CLEAR(PC)
		JSR	BYTE_FLAG_CLEAR(PC)

		MOVEQ.L	#0,D0
		MOVE.W	D0,COLOR_STATE(A5)
		MOVE.W	D0,COLOR_FLAG(A5)
		MOVE.W	D0,COLOR_TIMER(A5)
		MOVE.B	D0,START_FLAG2(A5)
		MOVE.W	D0,STOP_STEP(A5)
		MOVE.B	D0,FIRST_START(A5)
		BCLR.B	#0,MAKE_RANDOM(A5)
		BCLR.B	#0,READ_RANDOM(A5)
		MOVE.B	D0,LSPC_BUSY(A5)
		MOVE.B	#1,STOPPER(A5)
		MESS_ON
		MOVE.L	#M_SPRITE0_CLEAR,(A0)+
		MOVE.L	#M_FIX_CLEAR,(A0)+
		MESS_OFF

		RTS



M_SPRITE0_CLEAR:
		FIX_AUTO	1
		FIX_ADRS	0
		FIX_SAME	40H,0
		FIX_END

M_FIX_CLEAR:
		FIX_AUTO	1
		FIX_ADRS	0,0
		FIX_SAME	020H,020H
		FIX_SAME	0E0H,0FFH
		FIX_SAME	0E0H,0FFH
		FIX_SAME	0E0H,0FFH
		FIX_SAME	0E0H,0FFH
		FIX_SAME	0E0H,0FFH
		FIX_SAME	060H,0FFH
		FIX_SAME	020H,020H
		FIX_END




;
;	    *** PHYSICAL and LOGICAL WORK INTIALIZE ***
;

;		P(L)WORK all initialize
;		set	TYPE=0
;			WORK_No=itself number
;		use)	D0,A6

LWORK_INIT:
		LEA.L	LWORK_START(A5),A6
		MOVEQ.L	#11H,D0
LWORK_INIT_1:
		MOVE.W	#0,TYPE(A6)
		MOVE.B	D0,WORK_No(A6)
		LEA.L	100H(A6),A6
		ADDQ.W	#1,D0
		CMP.W	#71H,D0
		BCS.S	LWORK_INIT_1

		RTS

PWORK_INIT:
		LEA.L	PWORK_START(A5),A6
		MOVEQ.L	#10H,D0
PWORK_INIT_1:
		MOVE.W	#0,TYPE(A6)
		MOVE.B	D0,WORK_No(A6)
		LEA.L	100H(A6),A6
		ADDQ.W	#1,D0
		CMP.W	#70H,D0
		BCS.S	PWORK_INIT_1

		RTS

LPWORK_INIT:
		JSR	LWORK_INIT(PC)
		JSR	PWORK_INIT(PC)
		RTS




;
;	    *** SERCH FREE WORK ***
;

;		out)	NE (D0(.w)<>0)
;			 find free work A0
;			EQ (D0(.w)=0)
;			 not find free work
;		use)	D0,A0

FREE_LWORK:
		LEA.L	LWORK_START+1000H(A5),A0	044 only
		MOVEQ.L	#79-1,D0
		BRA.S	FREE_WORK_1
FREE_PWORK:
		LEA.L	PWORK_START(A5),A0
		MOVEQ.L	#96-1,D0
FREE_WORK_1:
		TST.W	TYPE(A0)
		BEQ	FREE_WORK_2

		LEA.L	100H(A0),A0
		DBRA	D0,FREE_WORK_1
FREE_WORK_2:
		ADDQ.W	#1,D0
		RTS


AFTER_FREE_WORK:

;		in)	A6=temporary P(L)WORK
;		out)	NE (D0(.b)<>0)
;			 find free work A0
;			EQ (D0(.b)=0)
;			 not find free work
;		use)	D0,A0

		LEA.L	(A6),A0
		MOVE.B	WORK_No(A6),D0
AFW_1:
		TST.W	TYPE(A0)
		BEQ	AFW_2

		LEA.L	100H(A0),A0
		ADDQ.B	#1,D0
		CMP.B	#70H,D0
		BCS.S	AFW_1
AFW_2:
		SUB.B	#6FH,D0
		RTS


PWORK_SET:

;		PWORK initialize
;		in)	A0 PWORK adrs
;			D2(.hw) TYPE (.lw) ACT_No
;			D3 (.w) X_POSITION
;			D4 (.w) Y_POSITION
;			D5 (.W) PRIORITY
;		use)	D0

		CLR.W	TYPE(A0)
		MOVE.W	D2,ACT_No(A0)
		SWAP	D2
		MOVE.W	D3,X_POSITION(A0)
		MOVE.W	D4,Y_POSITION(A0)
		MOVE.B	D5,PRIORITY(A0)
		MOVE.B	#1,ACT_DEC(A0)
		MOVE.B	#00100000B,ACT_ATTR(A0)		ACTAT_OFF
		MOVEQ.L	#0,D0
		MOVE.B	D0,ACT_FLAG(A0)
		MOVE.W	D0,X_POSITION+2(A0)
		MOVE.W	D0,Y_POSITION+2(A0)
		MOVE.L	D0,Z_POSITION(A0)
		MOVE.L	D0,VX(A0)
		MOVE.L	D0,VY(A0)
		MOVE.L	D0,VZ(A0)
		MOVE.W	D0,AX(A0)
		MOVE.W	D0,AY(A0)
		MOVE.W	D0,AZ(A0)
		MOVE.W	D0,DISP_X(A0)
		MOVE.W	D0,DISP_Y(A0)
		MOVE.B	D0,PALETTE_ADD(A0)
		MOVE.B	D0,FLASH_PALETTE(A0)
		MOVE.B	D0,STEP1(A0)
		MOVE.B	D0,STEP2(A0)
		MOVE.B	D0,FLAG(A0)
		MOVE.B	D0,HIT_FLAG(A0)
		MOVE.W	D0,HIT_ACTIVE(A0)
		MOVE.L	D0,WORK_N0(A0)
		MOVE.B	D0,MASTER_No(A0)
		MOVE.L	D0,HIT_OFS_X(A0)
		MOVE.L	D0,HIT_LEFT(A0)
		MOVE.L	D0,HIT_UPPER(A0)
		SUBQ.W	#1,D0
		MOVE.W	D0,SPRITE_POS(A0)
		MOVE.B	D0,ACT_TIMER(A0)
		MOVE.B	D0,ACT_COUNT(A0)
		MOVE.B	D0,BIG_X(A0)
		MOVE.B	D0,BIG_Y(A0)
		MOVE.W	D2,TYPE(A0)
		RTS

;
;	    *** ACTION etc. ***
;


OBJ_MAP_SET:
		ADDQ.B	#1,LSPC_BUSY(A5)
		ADDQ.B	#1,MESS_BUSY(A5)
		MOVE.L	(A0)+,D0
		MOVE.L	D0,OBJ1_MAP+OBJ_START(A5)
		MOVE.W	D0,OBJ1_MAP+OBJ_USE(A5)
		MOVE.W	(A0)+,OBJ1_MAP+DB_TYPE(A5)
		MOVE.L	(A0)+,D0
		MOVE.L	D0,OBJ2_MAP+OBJ_START(A5)
		MOVE.W	D0,OBJ2_MAP+OBJ_USE(A5)
		MOVE.W	(A0)+,OBJ2_MAP+DB_TYPE(A5)
		MOVE.L	(A0)+,D0
		MOVE.L	D0,OBJ3_MAP+OBJ_START(A5)
		MOVE.W	D0,OBJ3_MAP+OBJ_USE(A5)
		MOVE.W	(A0)+,OBJ3_MAP+DB_TYPE(A5)
		MOVE.L	(A0)+,D0
		MOVE.L	D0,OBJ4_MAP+OBJ_START(A5)
		MOVE.W	D0,OBJ4_MAP+OBJ_USE(A5)
		MOVE.W	(A0)+,OBJ4_MAP+DB_TYPE(A5)
		MOVE.L	A0,OBJ_DIV_POINT(A5)
		LEA.L	VPOS_BUFFER+2(A5),A0
		MOVEQ.L	#0,D0
		MOVE.W	#(380/2)-1,D7
OBJ_MAP_SET_1:
		MOVE.L	D0,(A0)+
		DBRA	D7,OBJ_MAP_SET_1

		MOVE.B	#80H,ORDER_BUFFER(A5)
		MOVE.B	#80H,ORDER_BUFFER+128(A5)
		SUBQ.B	#1,MESS_BUSY(A5)
		SUBQ.B	#1,LSPC_BUSY(A5)
		RTS



;
;
;	    *** calucurate ***
;
;


RAND16:

;		get 16bit random number (non sequencial)
;		out)	D0(.w) 16bit random number
;			all register keep

		MOVE.L	A0,-(SP)
		MOVEQ.L	#0,D0
		ADDQ.B	#2,READ_RANDOM(A5)
		MOVE.B	READ_RANDOM(A5),D0
		LEA.L	RANDOM_BUFFER(A5),A0
		MOVE.W	0(A0,D0.W),D0
		MOVE.L	(SP)+,A0
		RTS

RAND8:

;		get 8bit random number (sequencial)
;		out)	D0(.b) 8bit random number
;			all register keep

		MOVE.L	A0,-(SP)
		MOVEQ.L	#0,D0
		ADDQ.B	#1,RANDOM_SEED(A5)
		MOVE.B	RANDOM_SEED(A5),D0
		LEA.L	RND_DATA,A0
		MOVE.B	0(A0,D0.W),D0
		MOVE.L	(SP)+,A0
		RTS




;	    *** sin & cos ***

;		D0(.w)=D0*sin(D1.b),D0*cos(D1.b)
;		2pi=256
;		use)	D0(hi.w),D1(.w),A0

COS:
		SUB.B	#64,D1		cos(x)=sin(x+pi/2)
SIN:
		AND.W	#0FFH,D1
		NEG.B	D1
		BPL.S	SIN_1

		NEG.W	D0
SIN_1:
		ADD.W	D1,D1
		LEA.L	SIN_DATA,A0
		MOVE.W	0(A0,D1.W),D1
		CMPI.W	#1,D1		sin(D1)=1 ?
		BEQ.W	SIN_2

		TST.W	D0
		BMI.S	SIN_3

		MULU.W	D1,D0
		SWAP	D0
SIN_2:
		RTS
SIN_3:
		NEG.W	D0
		MULU.W	D1,D0
		SWAP	D0
		NEG.W	D0
		RTS



;		D0(.l)=D0*sin(D1.b),D0*cos(D1.b)
;		2pi=256
;		use)	D1(.w),D2(.l),A0

COS_L:
		SUB.B	#64,D1		cos(x)=sin(x+pi/2)
SIN_L:
		AND.W	#0FFH,D1
		NEG.B	D1
		BPL.S	SIN_L_1

		NEG.L	D0
SIN_L_1:
		ADD.W	D1,D1
		LEA.L	SIN_DATA,A0
		MOVE.W	0(A0,D1.W),D1
		CMPI.W	#1,D1
		BEQ.W	SIN_L_2

		JSR	MUL32(PC)
SIN_L_2:
		RTS


MUL32:
;		D0(.l)=D0(.l)*{D1(.w)/10000H}
;		use)	D2(.l)

		TST.L	D0
		BMI.S	MUL32_NEG

		MOVE.W	D0,D2
		MULU.W	D1,D2
		CLR.W	D2
		SWAP	D2
		SWAP	D0
		MULU.W	D1,D0
		ADD.L	D2,D0
		RTS
MUL32_NEG:
		NEG.L	D0
		MOVE.W	D0,D2
		MULU.W	D1,D2
		CLR.W	D2
		SWAP	D2
		SWAP	D0
		MULU.W	D1,D0
		ADD.L	D2,D0
		NEG.L	D0
		RTS

SEC_TIME:

;		second move timer decrement
;		in)	A0 timer address
;		out)	CS:time out

		SUBQ.B	#1,1(A0)
		BGT.S	SEC_TIME_1

		MOVE.B	SECOND_VALUE(A5),1(A0)
		SUBQ.B	#1,(A0)
SEC_TIME_1:
		RTS

SEC_TIME_BCD:

;		second move BCD timer decrement
;		in)	A0 timer address
;		use)	D0,D1

		SUBQ.B	#1,1(A0)
		BGT.S	SEC_TIME_BCD_1

		MOVE.B	SECOND_VALUE(A5),1(A0)
		SUB.B	D0,D0
		MOVE.B	(A0),D0
		MOVE.B	#1,D1
		SBCD.B	D1,D0
		MOVE.B	D0,(A0)
SEC_TIME_BCD_1:
		RTS




;
;	    *** ect. ***
;

PLAYABLE:
;		check play OK ?
;		out)	D0 d0:player 1  d1:player 2
;				0=can't play
;				1=play OK
;		all register keep

		MOVEM.L	D1-D7/A0-A6,-(SP)
		MOVE.L	#1000000H,CREDIT_DEC(A5)
		JSR	CREDIT_CHECK

		MOVEQ.L	#0,D0
		TST.B	CREDIT_DEC
		BEQ.S	PLAYABLE_1

		MOVEQ.L	#1,D0
PLAYABLE_1:
		MOVE.W	D0,-(SP)
		MOVE.W	#1,CREDIT_DEC

		JSR	CREDIT_CHECK

		MOVE.W	(SP)+,D0
		MOVEM.L	(SP)+,D1-D7/A0-A6
		TST.B	CREDIT_DEC+1(A5)
		BEQ.S	PLAYABLE_2

		ADDQ.B	#2,D0
PLAYABLE_2:
		CLR.L	CREDIT_DEC(A5)
		RTS



BIT_FLAG_CLEAR:
;		BIT_FLAGK all clear
;		use)	D0-D7(.l)=0
;			A0

		LEA.L	BIT_FLAG+100H(A5),A0
		MOVEQ.L	#0,D0
		MOVE.L	D0,D1
		MOVE.L	D0,D2
		MOVE.L	D0,D3
		MOVE.L	D0,D4
		MOVE.L	D0,D5
		MOVE.L	D0,D6
		MOVE.L	D0,D7
		REPT	8
		MOVEM.L	D0-D7,-(A0)
		ENDR
		RTS

BYTE_FLAG_CLEAR:
;		BYTE_FLAGK all clear
;		use)	D0-D7(.l)=0
;			A0

		LEA.L	BYTE_FLAG+100H(A5),A0
		MOVEQ.L	#0,D0
		MOVE.L	D0,D1
		MOVE.L	D0,D2
		MOVE.L	D0,D3
		MOVE.L	D0,D4
		MOVE.L	D0,D5
		MOVE.L	D0,D6
		MOVE.L	D0,D7
		REPT	8
		MOVEM.L	D0-D7,-(A0)
		ENDR
		RTS



		INCLUDE	WORK.INC

