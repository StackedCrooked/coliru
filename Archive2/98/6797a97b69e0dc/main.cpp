#include <iostream>   

int main()
{
    for(int k=0; k<10; ++k) {
        
        int UserNumber = 0;
        std::cout << "\nEnter any number other than 5: ";
        std::cin >> UserNumber;
        
        if (UserNumber == 5)
        {
            std::cout << "\n\n\nHey! You weren't supposed to enter 5!\n\n\n";
            exit(0);
        }

    }
    
    std::cout << "Wow, you're more patient then I am, you win.\n\n\n";
    return 0;
}