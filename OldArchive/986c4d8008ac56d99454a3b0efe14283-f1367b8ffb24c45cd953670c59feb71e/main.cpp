#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cerr << R"(to jest
    zawierająca
    znaki nowej linii
    moja wiadomość)" << std::endl;
    
    std::cerr <<
R"DEL(a to jest nowa 
wiadomość)" zawierająca
inne znaki
    i ciąg "))DEL" << std::endl;

    std::cerr << "Znaczki [\u2620]\u0E5B\u2764\u2764\u2764\u2764\u2764\u2764\u2764" << std::endl;

    std::cerr << u8"A to jest w utf-8. zażółć gęślą jaźń [\U00002018]" << std::endl;
    
    std::cerr << u8R"(A to jest raw i UTF-8 żółta jaźń)" << std::endl;
    
    std::string s = "żółć";
    std::cerr << s.size () << std::endl;
    
    s = u8"żółć";
    std::cerr << s.length () << std::endl;
}
