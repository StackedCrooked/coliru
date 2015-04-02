#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <stdint.h>
#include <map>
#include <iomanip>

class A { };

namespace Foo { class A { }; };


int main(int argc, const char* argv[]) {
    { 
        using namespace Foo; 
        
        new A();
    }
    
    new A();
    
    return 0;
}