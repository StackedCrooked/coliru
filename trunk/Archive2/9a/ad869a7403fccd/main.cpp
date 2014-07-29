#include <memory>
#include <iostream>

void FuckingCOM ( int** cominitializegogo ) {delete *cominitializegogo; *cominitializegogo = new int(48);}

int main () {    
    std::unique_ptr<int> meow( new int(24) );
    auto* ptr = meow.get();
    FuckingCOM ( std::addressof(ptr) );    
    std::cout << *meow << std::endl;
}