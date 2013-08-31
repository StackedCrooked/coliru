#include <memory>
#include <cstdlib>
#include <type_traits>

//[[annotate(randomattr)]]


namespace Arf __attribute__((annotate("arf"))) {
     
     struct __attribute__((annotate("woof"))) Woof {
         
         int __attribute__((annotate("howl"))) howlpower;
         
         void __attribute__((annotate("bark"))) Bark () {
             
         }
         
     };
 
}

int main() {
    
    
    
}