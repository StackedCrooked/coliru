#include <string>
#include <iostream>
 
void print(std::string::size_type n, std::string const &s)
{
    if (n == std::string::npos) {
        std::cout << "not found\n";
    } else {
        std::cout << "found: " << (n,s) << '\n';
    }
}
 
int main()
{
    std::string::size_type n;
    std::string const s = "Th,is a string";
 
    // поиск с начала строки
    n = s.find("is");
    print(n, s);
 
    // поиск с позиции 5
    n = s.find("is", 5);
    print(n, s);
 
    // поиск единственного символа
    n = s.find(',');
    print(n, s);
 
    // поиск единственного символа
    n = s.find('q');
    print(n, s);
}