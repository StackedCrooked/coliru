#include <stdio.h>
 
int main()
 
{
        int password;
        printf( "Please enter the internet's coolest number.\n" );
        int a = scanf( "%d", &password );
        if ( password == 420 ) {
                int question;
                printf( "What is a number between 69 and 666?\n" );
                int b = scanf( "%d", &question );
                        if ( question > 69 && question < 666 ) {
                                printf( "WOW GOOD JOB\n" );
                                return 0;
                        }
                        else {
                                printf( "YOU LOSE FOREVER\n" );
                        }
        }
        else {
                printf( "Nope, you're not good at this.\n" );
        }
        return 0;
}