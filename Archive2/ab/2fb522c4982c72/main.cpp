#include<vector>
#include<string>
#include<iostream>

class Foo
{
public:

   Foo(Foo&&) noexcept = default;
   Foo& operator=(Foo&&) noexcept = default;

   Foo()
   {
   }

private:

   std::vector<std::string> vectorFoo_;
};
int main()
{
    Foo Foo;
    std::cout << &Foo << std::endl;
}
