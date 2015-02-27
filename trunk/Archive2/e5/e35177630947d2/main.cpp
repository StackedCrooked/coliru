
#include <iostream>

using namespace std;

class MyClass {
   int value;

public:
   explicit MyClass(int value)
      : value {value}
   {
      cout << "ctor value " << value << '\n';
   }

   MyClass(const MyClass &src)
      : value {src.value}
   {
      cout << "ctor copy " << value << '\n';
   }

   MyClass(MyClass &&src)
      : value {src.value}
   {
      cout << "ctor move " << value << '\n';
   }

   ~MyClass(){
      cout << "dtor " << value << '\n';
   }

   int getValue() const
   {
      return this->value;
   }

};

MyClass test(void)
{
   MyClass x {10};
   return x;
}

int main()
{
   MyClass z = test();
}

