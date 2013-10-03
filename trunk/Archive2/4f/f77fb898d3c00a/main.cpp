#include <iostream>
template <class T>
class A
{
public:
    static constexpr int arr[5] = {1,2,3,4,5};
};

template<class T> constexpr int A<T>::arr[5];

int main()
{
    A<int> a;
    std::cout << a.arr[0] << std::endl;
    return 0;
}