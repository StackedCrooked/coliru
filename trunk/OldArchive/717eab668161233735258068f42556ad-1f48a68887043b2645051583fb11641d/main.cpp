#include <iostream>
#include <fstream>

template<class Ch, class Tr>
void func(std::basic_istream<Ch, Tr>& in) {
    std::cout << "std::cin here...";
}

template<class Ch, class Tr>
void func(std::basic_ifstream<Ch, Tr>& in) {
    std::cout << "\nstd::ifstream here..";
}

int main(){
    func(std::cin);
    std::ifstream in;
    func(in);
}