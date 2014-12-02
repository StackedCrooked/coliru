#include <stdio.h>
#include <stdint.h>

union LambdaBox {                                                           
    struct {                                                                
        uint64_t full;                                                      
        char lambda[];                                                      
    } data;                                                                 
    char padding[64];                                          
};

int main(){
    // This works
    printf("The total size allowed is %zu\n", 56L);
    // This also works
    printf("The total size of LambdaBox is %zu\n", sizeof(LambdaBox));

    // What is the correct syntax for the semantic meaning of the following line?
    printf("The total size allowed is %zu\n", sizeof(LambdaBox) -
            sizeof(decltype(LambdaBox::data)::full));
}