#include <iostream>
#include <string>
#include <vector>

int main()
{

    bool checkValidCharacters(const char* input)
    {
        std::string checkString(input);
        bool validCharacters = false;
        std::size_t found = checkString.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZàâäèêëîôùûüÿçÀÂÄÈÉÊÎÏÔÙÛÜŸÇ-. ");
        if (found != std::string::npos)
        {
            printf("Error: Invalid character: %c", input[found]);
        }
        else
        {
            printf("All characters valid\n");
            validCharacters = true;
        }
        return validCharacters;
    }
    
    std::cout << checkValidCharacters("TESTE");

}
