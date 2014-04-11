#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string message = "hi how are you";
    
    std::cout << "Message  : " << message << std::endl;
    
    std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c){ if(isalpha(c) && (c=tolower(c)) && (c+= 13) && c > 'z') c -= 26; return c;});
    
    std::cout << "Encrypted: " << message << std::endl;
    
    std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c){ if(isalpha(c) && (c=tolower(c)) && (c-= 13) && c < 'a') c += 26; return c;});
    
    std::cout << "Decrypted: " << message << std::endl;
}