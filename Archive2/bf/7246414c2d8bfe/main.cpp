#include <iostream>
 
template<typename T>
class Foo {
 public:
    Foo(const T& val) : data(val) {}
 private:
    T data;
 
    // generates a non-template operator<< for this T
    friend std::ostream& operator<<(std::ostream& os, const Foo& obj)
    {
        return os << obj.data;
    }
};
 
int main()
{
    Foo<double> obj(1.23);
    std::cout << obj << '\n';
}