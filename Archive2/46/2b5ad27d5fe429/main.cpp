#include <iostream>
#include <string>
#include <vector>
#include <cstring>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void swap(void* p, void* q, int size)
{
    char buffer[size];
    memcpy(buffer,p,size);
    memcpy(p,q,size);
    memcpy(q,buffer,size);
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

    char* s1 = "hello";
    char* s2 = "world";
    swap(&s1, &s2, sizeof(char*));
    std::cout << "Size of char* " << sizeof(char*) << std::endl;
    std::cout << "Size of void* " << sizeof(void*) << std::endl;
    std::cout << "Size of int* " << sizeof(int*) << std::endl;
    std::cout << s1 << " " << s2 << std::endl;
}
