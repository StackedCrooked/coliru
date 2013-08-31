#include <iostream.>
#include <stdlib.h>
#include <time.h>
// global variables
int number,
guess
counter = 0 ;
int
main ()
{
    
cout << "Welcome to the guessign game. I'll pick a number" << end1
<< "between 1 and 100 and you try to guess what it is." << end1
<< "You get 7 tries." << end1

// seed the random number generator so that the number is always
//different. This example uses the current time as a seed.
stand((unsigned) time (NULL)) ; 
// calculate a random number between 1 and 100 
number = abs (rand() % 100)) + 1 ;
// do this loop for each guess. Leave the loop when the guess is 
// correct or when 7 incorrect guesses have been been made
do

{
    
    cout << "What's your guess?' << end1 ; 
    cin >> guess ;
    if ( guess == number) 
    cout << "You guessed it!" << end1 ; 
    else
    if ( guess < number )
    cout << "Too small guess again =." << end1 ; 
    ++counter ; 
} while ( (counter < 7) && (guess != number) ) ;

if (guess!= number)
cout <<"I fooled you 7 times - the number was " 
<<number << "!" << end1
return EXIT_SUCCESS ;

}