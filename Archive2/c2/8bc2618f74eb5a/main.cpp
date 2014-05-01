#include <iostream>
#include <string>
#include <vector>

/*template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}*/

using namespace std;
struct X{};
X y;
//template <class X>
/*void foo(X&)
{cout << "Inside Lval" << endl;}*/

//template <class X>
void foo(X&&)
{cout << "Inside Rval" << endl;}

X ret()
{ return y; }

int main()
{
  //int x = 10;
  X x;
  foo(x);
  foo(ret());
  //int y = ret();
  //foo(ret());
  //cout << y << endl;
}
