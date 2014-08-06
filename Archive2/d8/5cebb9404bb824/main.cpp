#include <stdio.h>

typedef struct { 
   int Board[128]; 
   int WhiteToMove; 
   int Castling; // KQkq 
   int EnPassant; 
   int Halfmove; 
   int Valid; // Here is what GCC does not see. 
} Position; 

static const int Black = 0; 
static const int White = 1; 

static const int Nothing = 0; 

static const int WhitePawn = 1; 
static const int WhiteKnight = 2; 
static const int WhiteBishop = 3; 
static const int WhiteRook = 4; 
static const int WhiteQueen = 5; 
static const int WhiteKing = 6; 

static const int BlackPawn = 7; 
static const int BlackKnight = 8; 
static const int BlackBishop = 9; 
static const int BlackRook = 10; 
static const int BlackQueen = 11; 
static const int BlackKing = 12; 

int CastlingMask[128] = { 
   11, 16, 16, 16,  3, 16, 16,  7, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
   14, 16, 16, 16, 12, 16, 16, 13, 16, 16, 16, 16, 16, 16, 16, 16 
}; 

Position * MakeMove(Position * Pos, int Move) 
{ 
   int from = Move & 0x7F; 
   int dest = (Move >> 7) & 0x7F; 
   int flag = Move >> 14; 

   // Off the board testing in case my move generator has a bug 
   if (from & 0x88 || dest & 0x88) 
      Pos->Valid = 0; 

   Pos->Board[dest] = Pos->Board[from]; 
   Pos->Board[from] = Nothing; 

   Pos->WhiteToMove ^= 1; 

   // Castling, idea borrowed from DanaSah 
   Pos->Castling &= CastlingMask[from] & CastlingMask[dest]; 

   // Promotion 
   if (flag) { 
      if (flag == 1) 
         Pos->Board[dest] = (Pos->Board[dest] == WhitePawn) ? WhiteQueen : BlackQueen; 
      if (flag == 2) 
         Pos->Board[dest] = (Pos->Board[dest] == WhitePawn) ? WhiteRook : BlackRook; 
      if (flag == 3) 
         Pos->Board[dest] = (Pos->Board[dest] == WhitePawn) ? WhiteBishop : BlackBishop; 
      if (flag == 4) 
         Pos->Board[dest] = (Pos->Board[dest] == WhitePawn) ? WhiteKnight : BlackKnight; 
   } 

   // En Passant square, not yet tested 
   if (Pos->Board[dest] == WhitePawn && dest - from == 32) 
      Pos->EnPassant = from + 16; 
   else if (Pos->Board[dest] == BlackPawn && from - dest == 32) 
      Pos->EnPassant = dest + 16; 
   else Pos->EnPassant = 255; // Since we're using a 128 element board, 255 is obviously off the board 

   return Pos; 
} 

int main() 
{ 
    printf("it works\n"); 
    return 0; 
} 