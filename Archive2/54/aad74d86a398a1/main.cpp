#include <string>
#include <iostream>

struct X { 
    X()  { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~X() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    std::string x = "abc"; 
};

int main()
{
l1:
       std::string s = "hellow world";
       static int i = 0, j = 0, k = 0;
       if (i++)
           goto l2;
       else
           goto l1;

l2:
       X x;
       if (j++) goto more;
       goto l2;

more:
       if (k++<3)
           goto l1;

}
