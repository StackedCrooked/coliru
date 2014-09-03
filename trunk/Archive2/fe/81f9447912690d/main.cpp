#include <iostream>

template<typename T>
struct SelfRec {
    static const int value = SelfRec<T>::value;
};

int main()
{
    std::cout << SelfRec<int>::value << std::endl;
}
