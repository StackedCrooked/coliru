#include <iostream>

namespace N { class Foo; }

void bar(N::Foo&);

namespace N
{
    class Foo
    {
        friend void ::bar( Foo& f );
        void print(){ std::cout << "..." << std::endl; }    // private by default
    };
}

void bar( N::Foo& f )
{
    f.print();
}

int main()
{
}