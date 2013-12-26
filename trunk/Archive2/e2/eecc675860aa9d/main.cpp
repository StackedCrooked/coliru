#include <iostream>
#include <string>
#include <vector>

void purr ( char a ) {
    
}

void purr ( const char* a ) {
    
}

struct implicit {
    
    operator const char* () {
        return "meow";
    }
    
    operator int () {
        return 42;
    }
    
};

int main() {
    const char* meow = "meow";
    purr(meow);
    purr( implicit() );
}
