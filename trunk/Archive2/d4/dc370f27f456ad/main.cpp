#include <cstddef>

template<class T> struct Loop { Loop<T*> operator->(); };


int main () {
    
    Loop<int> i, j = i->hooray;
    
}
