#include <iostream>

template <class T>
class Mystack
{
public:
    friend std::ostream& operator<<(std::ostream& s, Mystack<T> const& d); 
};

template <class T>
std::ostream& operator<<(std::ostream& s, Mystack<T> const& d)
{
    //d.print(s);
    return s;
}

int main()
{
    Mystack<int> intstack;
    std::cout << intstack;

    return 0;
}