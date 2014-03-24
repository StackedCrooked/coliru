    #include <stdio.h>
    #include <string.h>
    
    typedef struct card {
        enum pips {ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} myPip;
        enum {SPADES, CLUBS, HEARTS, DIAMONDS} suit;
        char cardName[20];
    } card;
    
    int isXOfAKind(card *hand, int x, enum pips pip)
    {
        printf( "%d %d %d\n", hand->myPip, x, pip ) ;
        return 0 ;
    }
    
    void test( enum pips pip) {
       printf( "pip = %d\n", pip ) ;
    }
    
    int main()
    {
      test( TWO ) ;
      test( KING ) ;
      
      card card1 ;
      card1.myPip = QUEEN ;
      card1.suit = CLUBS ;
      strcpy( card1.cardName, "hello") ;
      
      isXOfAKind( &card1, 10, QUEEN ) ;
    }

