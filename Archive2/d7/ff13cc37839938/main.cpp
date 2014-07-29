#include <memory>
#include <iostream>

template<typename F, typename T> void call_with_ptrptr(std::unique_ptr<T>& t, F f) {
    auto* ptr = t.release();
    f( &ptr );  
    t.reset(ptr);    
}
void FuckingCOM ( int** cominitializegogo ) {delete *cominitializegogo; *cominitializegogo = new int(48);}

int main () {    
    std::unique_ptr<int> meow( new int(24) );
    call_with_ptrptr(meow, [](int** ptrptr) {
        FuckingCOM(ptrptr);
    });
    std::cout << *meow << std::endl;
}