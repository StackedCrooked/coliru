#include <iostream>

namespace poop
{
    namespace fecal_matter
    {
        namespace diarrhea
        {
            void foo(){std::cout << "foo\n";}
        }
    }
    void bar(){std::cout << "bar\n";}
}

int main()
{
    namespace poop = poop::fecal_matter::diarrhea;
    poop::foo();
    ::poop::bar();
}