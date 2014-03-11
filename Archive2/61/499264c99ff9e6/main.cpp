/* 
 * I dedicate this to my cat, and maybe my wife but I won't tell her because I
 * fear the consequences.
 *
 * I don't have a tortoise, but maybe from the prize money I can buy one, so I
 * can mention it in the dedications later?
 */

#include <iostream>

int main()
{
    std::cout << "Welcome, grasshopper!\nWhat is your life choice? ";
    
    std::string choice;
    if (std::cin >> choice)
        std::cout << "Sadly, you failed\n";
    else
        std::cout << "\nSometimes the winning move is not to play\nYou win.";
}
