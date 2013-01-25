#include <iostream>

void otherfunction() {}

template<class T>
void function(T) {
    throw otherfunction();
    return otherfunction();
}

int main ( int, char**) {
    try {
        function(3);
    } catch(void) {
        std::cout << "void caught";
    }
    
     return 0;
}