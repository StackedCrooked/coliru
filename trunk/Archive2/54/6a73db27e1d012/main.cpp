#include <iostream>
#include <string>
#include <chrono>

void f(std::string& s){
    auto newS(std::move(s));
    (void) sizeof newS;
    
}

int main()
{
    volatile auto start = std::chrono::high_resolution_clock::now();
    volatile auto i = std::chrono::high_resolution_clock::now() - start;
    (void) sizeof i;
    std::string miao = "gatto";
    std::cout << '|' <<  miao << '|' << std::endl;
    f(miao);
    std::cout << '|' <<  miao << '|' << std::endl;
    
	return 0;
}
