#include <iostream>

struct MyNumber
{
    operator int()
    {
        return num;
    }
    
    MyNumber operator++(int) //post-increment
    {
        MyNumber copy = *this;
        ++num;
        return copy;
    }
    MyNumber &operator++() //pre-increment
    {
        ++num;
        return *this;
    }

private:
    int num = 0;
};

int main()
{
    MyNumber n;
    std::cout <<      n      << std::endl; //0
    std::cout <<    ++n      << std::endl; //1
    std::cout <<      n      << std::endl; //1
    std::cout <<      n++    << std::endl; //1
    std::cout <<      n      << std::endl; //2
    std::cout << ++ ++n      << std::endl; //4
    std::cout <<      n      << std::endl; //4
    std::cout <<      n++ ++ << std::endl; //4
    std::cout <<      n      << std::endl; //5
}
