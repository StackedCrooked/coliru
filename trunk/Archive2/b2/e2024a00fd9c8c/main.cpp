#include <iostream> //this has std::cin and std::cout
#include <cstdlib> //this has the rand() which gives a random number

int main()
{
    int hidden_number = rand()%100;  //forces the random number to be less than 100
    int guess=0;
    int number_guesses = 0;
    do {
        std::cout << "enter a number: ";
        std::cin >> guess;
        number_guesses = number_guesses + 1;
        
        if (guess < hidden_number)
            std::cout << "too low!\n";
        if (guess > hidden_number)
            std::cout << "too high!\n";
            
    }while(guess != hidden_number);
    
    std::cout << "you guessed the number in " << number_guesses << " guesses!\n";
}
