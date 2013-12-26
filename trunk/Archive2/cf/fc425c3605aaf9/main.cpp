#include <iostream> //this has std::cin and std::cout
#include <cstdlib> //this has the rand() which gives a random number

int main()
{
    //The computer selects a number between 0 and 99 randomly
    int hidden_number = rand()%100;  //forces the random number to be less than 100
    int guess=0; //this will be the number that the user enters
    int number_guesses = 0; //this will hold the number of guesses the user enters
    
    do { //loop until the user guesses the right number
        std::cout << "enter a number: "; //prompt the user to type
        std::cin >> guess; //wait for the user to enter a number
        number_guesses = number_guesses + 1; //increase the guess count
        
        if (guess < hidden_number) //if they guess too low, 
            std::cout << "too low!\n"; //tell them they guessed too low
        else  //otherwise
            std::cout << "too high!\n"; //tell them they guessed too high
            
    }while(guess != hidden_number); //end the loop if they guessed the right number
    
    //tell them how many guesses it took
    std::cout << "you guessed the number in " << number_guesses << " guesses!\n";
}
