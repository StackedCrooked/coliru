#include <stdio.h>

typedef struct card {
    enum pips {ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} myPip;
    enum {SPADES, CLUBS, HEARTS, DIAMONDS} suit;
    char cardName[20];
} card;

void test( enum pips pip) {
   printf( "pip = %d\n", pip ) ;
}

int main()
{
  test( TWO ) ;
  test( KING ) ;
}