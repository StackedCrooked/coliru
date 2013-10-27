#include <iostream>

bool isPalindrome(char * string)
{
    int stringLength;
    
    for (stringLength = 0; ; ++stringLength)
        if (string[stringLength] == '\0')
            break;
        
    for (int i = 0; i < stringLength; ++i)
        if (string[i] != string[stringLength - (i + 1)])
            return false;
            
    return true;
}


int main()
{
    char * yes = "racecar";
    char * no = "word";
    
    std::cout << isPalindrome(yes) << std::endl;
    std::cout << isPalindrome(no) << std::endl;
	std::cin.get();
}