#include <assert.h>
#include <iostream>

template <bool B = true>
int g(int n){
    if(n == 0)
        return 1;
    return n + g<!B>(n-1);
}

int main(){
    std::cout << g(10) << std::endl;
}
