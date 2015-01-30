#include <iostream>

template <typename T = struct X>
class FunkyClass {
    struct Nested {
        typedef int blob;
        blob shalamar;
    };
    
    struct Wasted : public Nested {
        typename Nested::blob ouch;
        typename Nested::blob disco() {
            return this->shalamar;
        }
    };
public:
    Wasted X;
};

int main()
{
    FunkyClass<> t;
    std::cout << t.X.disco() << std::endl;
}