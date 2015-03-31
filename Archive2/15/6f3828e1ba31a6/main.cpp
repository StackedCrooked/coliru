#include <vector>

class A
{
public:
    class B
    {
    };
};


int main()
{
   std::vector<A::B> foo;
   return 0;
}