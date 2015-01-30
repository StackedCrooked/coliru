#include <iostream>

class FunkyClass {
    struct Nested {
        typedef int blob;
        blob shalamar;
    };
    
    struct Wasted : public Nested {
        blob ouch;
        blob disco() {
            return shalamar;
        }
    };
public:
    Wasted X;
};

int main()
{
    FunkyClass t;
    std::cout << t.X.disco() << std::endl;
}