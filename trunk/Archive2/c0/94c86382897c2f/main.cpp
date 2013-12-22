#include <iostream>
#include <string>
#include <vector>

void purr ( char a ) {
    
}

void purr ( const char* a ) {
    
}

template <typename T>
struct increase_conversion_aversion {
    T item;
    
    increase_conversion_aversion( T item ) : item(item) {
    
    }
    
    operator T () {
        return item;
    }
};

struct implicit {
    
    operator const char* () {
        return "meow";
    }
    
    operator increase_conversion_aversion<int> () {
        return increase_conversion_aversion<int>( 42 );
    }
  
    template <typename T = int, typename X = typename std::enable_if<std::is_same<T, int>::value>::type>
    operator int () {
        return 42;
    } 
};

int main() {
    const char* meow = "meow";
    purr(meow);
    purr( implicit() );
    int convert = implicit{};
}
