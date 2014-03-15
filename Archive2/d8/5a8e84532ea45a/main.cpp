#include <array>
#include <iostream>

template<class Iterator, class T>
void a(Iterator, Iterator, const T&)
{
    std::cout << " a called\n";
}

template<typename T>
T g(const T& arg)
{
  return arg;
}

template<class T, size_t N>
void a(std::array<T, N>& theArray) {
    a(theArray.begin(), theArray.end(), g(T()));
}

int main()
{
    std::array<double, 5> someStdArray;
    a(someStdArray);

}