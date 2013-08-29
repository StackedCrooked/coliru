#include <memory>
#include <cstdlib>
#include <type_traits>

//[[annotate(randomattr)]]

#define reflect __attribute__((annotate("lib.reflect")))
#define reflect2 [[lib::reflect]]

namespace Arf reflect {
    struct reflect Woof {
         
        reflect int howlpower;
         
        reflect void Bark () {
             
        }
    };
}

namespace Arf2 {
    // has to go on inside
    reflect2;
    
    struct reflect2 Woof {
         
        reflect2 int howlpower;
         
        reflect2 void Bark () {
             
        }
    };
}

int main() {
    
    
    
}