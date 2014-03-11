#include <iostream>
#include <string>

int main()
{
    const std::string str = "solutomaattimittaamotulos";
    
    bool palindrome = true;
    for(auto it = str.begin(), it2 = str.end()-1; it < it2 && palindrome; ++it , --it2)
    //if the string is odd characters you can iterate while they are not equal
    //but for evens they will not equal each other
    {
        palindrome = *it == *it2;
    }
    
    if(palindrome)
    {
        std::cout << str << " is a palindrome." << std::endl;
    }
    else
    {
        std::cout << str << " is not a palindrome." << std::endl;
    }
}