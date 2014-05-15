#include <iostream>
struct A{

        A(int i) { std::cout << "constructing with i " << std::endl;}

};
std::ostream& operator<< (std::ostream &out, A &a)
{
    out << "printing out struct A"<< std::endl;
    return out;
}
template<typename T, T a = T{3}>
void f(){std::cout << a;};


int main()
{
  A a{3};
  std::cout << a;
  f<int>();
 // f<A>();  //#1
}
