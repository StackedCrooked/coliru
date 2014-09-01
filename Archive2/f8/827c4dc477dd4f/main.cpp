#include <iostream>

const 
class neolptr_t {
public:
    template<class T>
    inline operator T*() const { 
        return 0; 
    }
    
    template<class C, class T>
    inline operator T C::*() const { 
        return 0; 
    }
    
private:
    void operator&() const;  

} neolptr = {};


int main() {
    int* i = neolptr;
    
    std::cout << "Pointing to adress: " << i;
}