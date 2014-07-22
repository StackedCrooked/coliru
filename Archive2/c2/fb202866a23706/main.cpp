#include <stdio.h>

#define TOKEN_CAT_IMPL( x , y ) x##y
#define TOKEN_CAT( x , y ) TOKEN_CAT_IMPL(x,y)

#define SOME_ABSURD_MACRO( id ) TOKEN_CAT( this_is_completely_absurd_ , id )


#define ID 25

int SOME_ABSURD_MACRO(ID) = 0;

int main()
{
   this_is_completely_absurd_25 = 25;
   
   printf("%d",this_is_completely_absurd_25);
}