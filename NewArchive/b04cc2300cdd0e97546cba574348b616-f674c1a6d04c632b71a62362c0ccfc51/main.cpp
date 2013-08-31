#include <iostream>

namespace ns {
    struct Bar {
        Bar();
    };
    
    Bar::Bar() {
        void foo();
        foo();
    }
    
    void foo() {
        std::cout << "ns::foo";
    }
}

void foo() {
   std::cout << "::foo";
}

int main()
{
    ns::Bar();
}
