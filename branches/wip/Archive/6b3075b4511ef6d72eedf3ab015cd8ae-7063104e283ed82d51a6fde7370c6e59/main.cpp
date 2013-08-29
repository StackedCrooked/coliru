#include <iostream>
#include <memory>

template <typename T>
class vector_view {
private:
    T* elems;
    std::size_t sz;
    
public:
    vector_view( T* elements, std::size_t elementcount ) 
    : elems(elements), sz(elementcount) {
        
    }
    
    template<std::size_t N>
    vector_view( T(&array)[N] ) : elems(std::addressof(array[0])), sz(N) {
        
    }
    
    template <typename TContainer>
    vector_view( TContainer& container ) : elems(container.data()), sz(container.size()) {
        
    }
    
    T& operator[] ( std::size_t i ) {
        return elems[i];
    }
    
    const T& operator[] ( std::size_t i ) const {
        return elems[i];
    }
    
    T* data () {
        return elems;
    }
    
    const T* data () const {
        return elems;
    }
    
    std::size_t size() {
        return sz;
    }
};


template<typename T, size_t N>
void array_view(const T(&array)[N]) {
    std::cout << "Viewing array" << std::endl;
}

int main() {
    int a[5] = {1,2,3,5};
    array_view(a);
    vector_view<int> arf( a );
    std::cout << arf[0] << std::endl;
}