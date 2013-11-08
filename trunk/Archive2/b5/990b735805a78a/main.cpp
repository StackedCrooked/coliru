#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<char> v;
    std::cout << v.capacity() << "\n";
    v.reserve(10);
    std::cout << v.capacity() << "\n";
    v[0] = 'a';
    v[2] = 'b';
    v[3] = 'c';
    v[4] = 'd';
    v[5] = 'e';
    std::string s(v.begin(), v.end());
    std::cout << "["<< s << "]" << "\n";
}
