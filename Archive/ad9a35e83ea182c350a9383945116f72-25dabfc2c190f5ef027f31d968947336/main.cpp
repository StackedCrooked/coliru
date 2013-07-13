#include <memory>
#include <cstdlib>
#include <type_traits>

//[[annotate(randomattr)]]

#define reflect __attribute__((annotate("reflect")))

namespace Arf reflect {
     
     struct Woof {
         
         int howlpower;
         
         void Bark () {
             
         }
         
     };
 
}

int main() {
    
    
    
}