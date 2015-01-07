#include <iostream>

template<typename T>
void func(const T type)
{
    std::cout << "I like all types" << std::endl;
}

template<>
void func(const int type)
{
    std::cout << "I just like ints" << std::endl;
}

int main()
{
    int i = 0;
    func(i);
    {
        auto j = i;
        func(j);
    }
    {
        auto j = i + 2;
        func(j);
    }
    {
        auto j = i / 2;
        func(j);
    }
    {
        auto j = i / 2.0;
        func(j);
    }
  return 0;
}
